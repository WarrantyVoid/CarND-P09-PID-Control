#ifndef PID_H
#define PID_H

class PID
{
public:
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();


public:
  /*
  * Initialize PID.
  */
  void Init(double KP, double KI, double KD);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the steering.
  */
  double GetSteering() const;

private:
  double mErrorP;
  double mErrorI;
  double mErrorD;
  bool mHasLastError;
  double mLastError;
  double mKP;
  double mKI;
  double mKD;
};

#endif /* PID_H */
