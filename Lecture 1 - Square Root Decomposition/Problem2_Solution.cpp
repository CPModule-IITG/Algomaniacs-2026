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
int n, q, blk, cnt;
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
    if(freq[x] % 2 == 0) cnt--;
    else cnt++;
}

void rem(int id){
    int x = a[id];
    freq[x]--;
    if(freq[x] % 2 == 0) cnt--;
    else cnt++;
}

void reset(int n){
    for(int i = 0; i < n; i++) freq[a[i]] = 0;
    cnt = 0;
}

void solve(){

    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) cin >> a[i];
    blk = sqrt(n);

    vector<query> queries(q);

    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        queries[i].l = l - 1;
        queries[i].r = r - 1;
        queries[i].idx = i;
    }

    sort(all(queries), compare);

    vector<int> ans(q);
    int curr_l = 0, curr_r = -1;
    for(int i = 0; i < q; i++){
        int l = queries[i].l;
        int r = queries[i].r;

        while(curr_l > l){
            curr_l--;
            add(curr_l);
        }
        while(curr_r < r){
            curr_r++;
            add(curr_r);
        }

        while(curr_l < l){
            rem(curr_l);
            curr_l++;
        }
        while(curr_r > r){
            rem(curr_r);
            curr_r--;
        }

        ans[queries[i].idx] = cnt;
    }

    for(int i = 0; i < q; i++){
        if(ans[i] == 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    reset(n);
}

signed main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test;
    cin >> test;

    for(int i = 1; i <= test; i++){
        solve();
    }

    return 0;
}
