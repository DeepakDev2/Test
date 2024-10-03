#include <bits/stdc++.h>
using namespace std;

// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
// // // find_by_order and order_of_key

#define vi vector<int>
#define vivi vector<vector<int>>
#define vivivi vector<vector<vector<int>>>

#define endl "\n"
#define MOD 1000000007
#define int long long int

vector<int> segTree;

void build(vector<int> &arr, int start, int end, int index)
{
    if (start == end)
    {
        segTree[index] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    int left = 2 * index, right = 2 * index + 1;
    build(arr, start, mid, left);
    build(arr, mid + 1, end, right);
    segTree[index] = segTree[left] + segTree[right];
}

void update(vector<int> &arr, int start, int end, int index, int pos, int value)
{
    if (start == end)
    {
        arr[pos] = value;
        segTree[index] = arr[pos];
        return;
    }
    int mid = (start + end) / 2;
    if (mid >= pos)
    {
        update(arr, start, mid, 2 * index, pos, value);
    }
    else
    {
        update(arr, mid + 1, end, 2 * index + 1, pos, value);
    }
    segTree[index] = segTree[index * 2 + 1] + segTree[2 * index];
}

int query(int start, int end, int index, int l, int r)
{ // give sum from l to r
    if (l <= start && end <= r)
    {
        // complete overlap
        return segTree[index];
    }
    else if (r < start || l > end)
    {
        return 0;
    }
    int mid = (start + end) / 2;
    return query(start, mid, 2 * index, l, r) + query(mid + 1, end, 2 * index + 1, l, r);
}

void solve(int testcase)
{
    int n;
    cin >> n;
    segTree.resize(2 * n + 1, -1);
    vi arr(n);
    for (int &i : arr)
        cin >> i;
    build(arr, 0, n - 1, 1);

    update(arr, 0, n - 1, 1, 1, 3);
    for (auto i : segTree)
    {
        cout << i << " ";
    }
    cout << endl;
    cout << query(0, n - 1, 1, 0, 2) << endl;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve(t + 1);
    }
    return 0;
}