#include <Rcpp.h>
using namespace Rcpp;

class GroupFixed {
    const Fast<NumericVector> x_;
    double width_;
    double origin_;
  public:
    GroupFixed (const NumericVector& x, double width, double origin = 0)
       : x_(x), width_(width), origin_(origin) {
    }

    int bin(int i) const {
      if (ISNAN(x_[i])) return 0;
      
      return (x_[i] - origin_) / width_ + 1;
    }

    int size() const {
      return x_.size();
    }
};

class GroupBreaks {
    const Fast<NumericVector> x_;
    const NumericVector& breaks_;
    NumericVector::const_iterator breaks_it_, breaks_end_;

  public:
    GroupBreaks (const NumericVector& x, const NumericVector& breaks)
        : x_(x), breaks_(breaks) {
      breaks_it_ = breaks.begin();
      breaks_end_ = breaks.end();
    }

    int bin(int i) const {
      if (ISNAN(x_[i])) return 0;

      NumericVector::iterator
        bin_it = std::upper_bound(breaks_it_, breaks_end_, x_[i]);

      return std::distance(breaks_it_, bin_it);
    }

    int size() const {
      return x_.size();
    }
};