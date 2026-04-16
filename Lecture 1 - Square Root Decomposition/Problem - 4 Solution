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

struct query{
    int l, r, k, idx;
};  

void solve(){

    int n, m;
    cin >> n >> m;

    int blk = sqrt(n);
    vector<int> a(n);
    for(auto &i : a) cin >> i;

    vector<query> q(m);
    for(int i = 0; i < m; i++){
        int l, r, k;
        cin >> l >> r >> k;
        q[i].l = l - 1;
        q[i].r = r - 1;
        q[i].k = k;
        q[i].idx = i;
    }

    sort(all(q), [&](const query &x, const query &y) {
        if(x.l / blk != y.l / blk) {
            return x.l / blk < y.l / blk;
        }
        return x.r < y.r;
    });

    vector<int> ans(m);
    vector<int> freq(3e5 + 1, 0);
    vector<int> block_freq(blk + 10);

    int curr_l = 0, curr_r = -1;

    auto add = [&](int id) {
        int x = a[id];
        freq[x]++;
        block_freq[x / blk]++;
    };

    auto rem = [&](int id) {
        int x = a[id];
        freq[x]--;
        block_freq[x / blk]--;
    };

    for(auto qry : q){
        int l = qry.l;
        int r = qry.r;

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

        int len = r - l + 1;
        len /= qry.k;

        ans[qry.idx] = -1;
        for(int i = 0; i <= n / blk + 1; i++){
            if(block_freq[i] <= len) continue;
            for(int j = i * blk; j < min((int)3e5 + 1, (i + 1) * blk); j++){
                if(freq[j] > len){
                    ans[qry.idx] = j;
                    break;
                }
            }
            if(ans[qry.idx] != -1) break;
        }
    }

    for(auto i : ans) cout << i << endl;
}

signed main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
