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

void solve(){
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    int blk = sqrt(n);
    vector<int> id(n + 1);
    vector<int> cnt(n + 1);

    for(int i = n; i >= 1; i--){
        int b = i / blk;
        if(i + a[i] > n){
            id[i] = n + 1;
            cnt[i] = 1;
        }
        else{
            int b1 = (i + a[i]) / blk;

            if(b1 == b){
                id[i] = id[i + a[i]];
                cnt[i] = 1 + cnt[i + a[i]];
            }
            else{
                id[i] = i + a[i];
                cnt[i] = 1;
            }
        }
    }

    for(int qu = 0; qu < q; qu++){
        int tp;
        cin >> tp;

        if(tp == 0){
            int idx, x;
            cin >> idx >> x;

            int b = idx / blk;
            a[idx] = x;
            for(int i = idx; i / blk == b && i >= 0; i--){
                if(i + a[i] > n){
                    id[i] = n + 1;
                    cnt[i] = 1;
                }
                else{
                    int b1 = (i + a[i]) / blk;

                    if(b1 == b){
                        id[i] = id[i + a[i]];
                        cnt[i] = 1 + cnt[i + a[i]];
                    }
                    else{
                        id[i] = i + a[i];
                        cnt[i] = 1;
                    }
                }
            }
        }
        else{
            int idx;
            cin >> idx;

            int curr = idx;
            int tot = 0;
            int last = idx;

            while(curr <= n){
                tot += cnt[curr];
                last = curr;
                curr = id[curr];
            }

            curr = last;

            while(curr <= n){
                last = curr;
                curr += a[curr];
            }

            cout << last << " " << tot << endl;
        }
    }
}

signed main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
