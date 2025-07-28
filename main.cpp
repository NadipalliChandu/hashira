#include <iostream>
#include <vector>
using namespace std;

int polynomial(int x, int secret, int a1, int a2) {
    return secret + a1 * x + a2 * x * x;
}

vector<pair<int, int>> generate_shares(int secret, int n, int a1, int a2) {
    vector<pair<int, int>> shares;

    for (int i = 1; i <= n; i++) {
        int y = polynomial(i, secret, a1, a2);
        shares.push_back({i, y}); // Store the (x, y) pair as a share
    }

    return shares;
}

int reconstruct_secret(const vector<pair<int, int>>& shares) {
    int x1 = shares[0].first, y1 = shares[0].second;
    int x2 = shares[1].first, y2 = shares[1].second;
    int x3 = shares[2].first, y3 = shares[2].second;

    int secret =
        y1 * (x2 * x3) / ((x1 - x2) * (x1 - x3)) +
        y2 * (x1 * x3) / ((x2 - x1) * (x2 - x3)) +
        y3 * (x1 * x2) / ((x3 - x1) * (x3 - x2));

    return secret;
}

int main() {
    int secret = 123;

    int n = 5;

    int a1 = 2, a2 = 3;

    auto shares = generate_shares(secret, n, a1, a2);

    cout << "Generated Shares:\n";
    for (auto [x, y] : shares) {
        cout << "(" << x << ", " << y << ")\n";
    }

    vector<pair<int, int>> sample = { shares[0], shares[1], shares[2] };
    int recovered = reconstruct_secret(sample);

    cout << "\nRecovered Secret: " << recovered << endl;

    return 0;
}
