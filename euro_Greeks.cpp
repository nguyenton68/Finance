/* Calculate delta using formula of call/put option from black-scholes different equation
 * C(S,K,T,v,r)
 * Delta = C' = C(S+h)-C(S) /h
 */
#include "black_scholes.h"
using namespace std;
// This uses the forward difference approximation to calculate the Delta of a call option
double call_delta_fdm(const double S, const double K, const double r, const double v, const double T, const double delta_S) {
  return (call_price(S + delta_S, K, r, v, T) - call_price(S, K, r, v, T))/delta_S;
}

// This uses the centred difference approximation to calculate the Gamma of a call option
double call_gamma_fdm(const double S, const double K, const double r, const double v, const double T, const double delta_S) {
  return (call_price(S + delta_S, K, r, v, T) - 2*call_price(S, K, r, v, T) + call_price(S - delta_S, K, r, v, T))/(delta_S*delta_S);
}

int main() {
  // First we create the parameter list
  double S = 100.0;        // Option price
  double delta_S = 0.001;  // Option price increment
  double K = 100.0;        // Strike price
  double r = 0.05;         // Risk-free rate (5%)
  double v = 0.2;          // Volatility of the underlying (20%)
  double T = 1.0;          // One year until expiry
    
  // Then we calculate the Delta and the Gamma for the call
  double call_delta_f = call_delta_fdm(S, K, r, v, T, delta_S);
  double call_gamma_f = call_gamma_fdm(S, K, r, v, T, delta_S);

  // Finally we output the parameters and greeks
  cout<<"Underlying:        " << S<<endl;
  cout<<"Delta underlying:  " << delta_S<<endl;
  cout<<"Strike:            " << K<<endl;
  cout<<"Risk-Free Rate:    " << r<<endl;
  cout<<"Volatility:        " << v<<endl;
  cout<<"Maturity:          " << T << std::endl<<endl;

  cout<<"Call Delta:        " << call_delta_f<<endl;
  cout<<"Call Gamma:        " << call_gamma_f<<endl;
}
