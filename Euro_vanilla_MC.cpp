/* 
 * European vanilla pricing using MC (numerical method)
 * Simulated uniform distributed random number using Box-Muller method (wiki)
 * Calculate expectation payoff of call/put by summing all S(t) at each interval
 * then divided by total number of even thrown
 * Discounted expectation payoff = e^(-Tr)*E[S(t)]
 * where S(t) = S_0 * e^{r-sigma*sigma)*T +sigma*sqrt(T)*rand()}
 * Input: stock price, strike price, rate, volatility...
 * Output: call/put price
 */
#include <algorithm>    // Needed for the "max" function
#include <cmath>
#include <iostream>
using namespace std;

const int N=10000000;
// use Box-Muller algorith to generate
// gaussian random numbers 
// 0 expectation; 1 variance
double gaussian_box_muller() {
  double x = 0.0;
  double y = 0.0;

  // Continue generating two uniform random variables
  // until the radius is <=1
  do {
    x = 2.0 * rand() / (double)(RAND_MAX)-1;
    y = 2.0 * rand() / (double)(RAND_MAX)-1;
  } while (x*x+y*y >= 1.0);

  //return uniform distributed random variable from 0,1
  return x*sqrt(-2*log(x*x+y*y)/(x*x+y*y));
}

// Pricing a European vanilla call option with a Monte Carlo method
double call_price(const int& N, const double& S, const double& K, const double& r, const double& v, const double& T) {
  double S_adjust = S * exp(T*(r-0.5*v*v));
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  for (int i=0; i<N; i++) {
    double gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * exp(v*sqrt(T)*gauss_bm);
    payoff_sum += max(S_cur - K, 0.0);
  }
  //discounted expectation payoff
  return (payoff_sum / (double)(N)) * exp(-r*T);
}

// Pricing a European vanilla put option with a Monte Carlo method
double put_price(const int& N, const double& S, const double& K, const double& r, const double& v, const double& T) {
  double S_adjust = S * exp(T*(r-0.5*v*v));
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  for (int i=0; i<N; i++) {
    double gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * exp(v*sqrt(T)*gauss_bm);
    payoff_sum += max(K - S_cur, 0.0);
  }
  // discounted expectation of payoff
  return (payoff_sum / (double)(N)) * exp(-r*T);
}

int main() {
  // the parameter list                                                                               
  int N = 10000000;   // Number of simulated asset paths                                                       
  double S = 100.0;  // Option price                                                                                  
  double K = 100.0;  // Strike price                                                                                  
  double r = 0.05;   // Risk-free rate (5%)                                                                           
  double v = 0.2;    // Volatility of the underlying (20%)                                                            
  double T = 1.0;    // One year until expiry                                                                         

  // Then we calculate the call/put values via Monte Carlo                                                                          
  double call = call_price(N, S, K, r, v, T);
  double put = put_price(N, S, K, r, v, T);

  // Finally we output the parameters and prices                                                                      
  cout<<"Number of Paths: " << N <<endl;
  cout<<"Underlying:      " << S <<endl;
  cout<<"Strike:          " << K <<endl;
  cout<<"Risk-Free Rate:  " << r <<endl;
  cout<<"Volatility:      " << v <<endl;
  cout<<"Maturity:        " << T <<endl;
  cout<<"Call Price:      " << call <<endl;
  cout<<"Put Price:       " << put <<endl;

  return 0;
}
