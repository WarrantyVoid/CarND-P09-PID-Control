#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <vector>
class PID;
typedef std::vector<double> TParameters;

enum ETwiddleResult
{
  None,
  RunFinished,
  TwiddleFinished
};

class Twiddle
{
public:
  /**
  * Constructor
  */
  Twiddle(PID &pid1, PID &pid2, double tolerance);

  /**
  * Destructor.
  */
  virtual ~Twiddle();

public:
  /**
  * Initialize Twiddle.
  */
  void Init(int numRuns, const TParameters &parameters, const TParameters &deltas);

  /**
   * @brief Update
   * @param cte
   * @return
   */
  ETwiddleResult Update(double cte);

private:
  PID &mPID1;
  PID &mPID2;
  double mTolerance;
  int mNumRuns;
  int mCurRun;
  TParameters mParameters;
  TParameters mDeltas;
  int mCurParameter;
  double mBestError;
  bool mIsIniRun;
  bool mIsInvRun;
};

#endif /* TWIDDLE_H */
