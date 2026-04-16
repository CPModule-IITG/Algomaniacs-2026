#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast,unroll-loops")

#define int long long
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

using namespace std;
using namespace __gnu_pbds;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; // find_by_order, order_of_key

const int MAXN = 1e6 + 1;
const int blk = sqrt(MAXN);
int curr_ans = 0;
vector<int> a(MAXN);
vector<int> freq(MAXN, 0);

struct query{
    int l, r, idx;
};

bool compare(query &a, query &b){
    if(a.l / blk != b.l / blk){
        return a.l / blk < b.l / blk;
    }
    return a.r < b.r;
}

void add(int id){
    int x = a[id];
    freq[x]++;
    if(freq[x] == 1){
        curr_ans++;
    }
}

void remove(int id){
    int x = a[id];
    freq[x]--;
    if(freq[x] == 0){
        curr_ans--;
    }
}

void solve(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];

    int m;
    cin >> m;
    vector<query> q(m);
    for(int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        q[i].l = l - 1;
        q[i].r = r - 1;
        q[i].idx = i;
    }

    sort(all(q), compare);

    int curr_l = 0, curr_r = -1; // Empty window
    vector<int> ans(m);
    for(int i = 0; i < m; i++){
        int l = q[i].l;
        int r = q[i].r;
        int idx = q[i].idx;
        
        // 1. Expand Window
        while(curr_l > l){
            curr_l--;
            add(curr_l);
        }
        while(curr_r < r){
            curr_r++;
            add(curr_r);
        }

        // 2. Shrink Window
        while(curr_l < l){
            remove(curr_l);
            curr_l++;
        }
        while(curr_r > r){
            remove(curr_r);
            curr_r--;
        }

        ans[idx] = curr_ans;
    }

    for(int i = 0; i < m; i++) cout << ans[i] << endl;
}

signed main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
