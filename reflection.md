
## Reflection

### PID Project

The goals / steps of this project are the following:

* Your code must compile without errors with cmake and make.
* The PID procedure follows what was taught in the lessons.
* Student describes the effect of the P, I, D component of the PID algorithm in their implementation.
* Student discusses how they chose the final hyperparameters (P, I, D coefficients).
* The vehicle must successfully drive a lap around the track.

[//]: # (Image References)
[image1]: ./img/proportional.png
[image2]: ./img/differential.png

### Rubric Points
Here I will consider the reflection points of the [rubric](https://review.udacity.com/#!/rubrics/824/view) individually and describe how I addressed each point in my implementation.  

---

#### 1. Describe the effect each of the P, I, D components had in your implementation.

#####Proportional component

The proportional component expresses the base steering correction as linear function of the signed cross track error (cte). One effect of this is, that it causes the vehicle to overshoot, resulting in a wave along the reference path. I don't know the movement model of the Udacity simulator car, but with the bicycle movement model of the Robot class, this wave always gets amplified over time by the controller:

![Proportional component][image1]

The amount of amplification depends on the velocity of the vehicle as well as the factor 'tau_p'. For larger velocities, non-linear smaller values of 'tau_p need' to be chosen in order to keep the vehicle stable for as long as possible. The final result of amplification will always be an ellipsoid movement.

#####Differential component

The differential component expresses the correction to the proportional component in order to avoid overshooting and amplification. It causes an overlaying 2nd wave to the P component based on the difference in cross errors between last two measurements. This component can diminish the amplitude of the P components wave, but can also cause various error effects, if 'tau_d' is selected in an too large proportion towards 'tau_p'. But generally, the larger 'tau_d' towards 'tau_p', the smoother is the approach to the reference path. 

![Differential component][image2]

The differential component normally would need to take also the time difference into account, but since I assume that simulator frames are sent with a constant interval, the delta time can be simply factorized into 'tau_d'.

#####Integral component

The integral component expresses the correction to steering over driving time. It seeks to  balance the positive and negative cross error measurements and can help to defeat biased steering controls. As the simulator has no bias, this has no significant effect on control. The twiddle optimizer usually ends up with a 'tau_i' near zero. If chosen too high, the integral component will support overshooting again.


#### 2. Describe how the final hyper parameters were chosen.

I've started out with the hyper parameters given in the lesson:
* tau_p = 0.2
* tau_i = 0.004
* tau_d = 3.0

which resulted in a mse to reference path of **0.208** after 1000 frames.

These values have already lead to a  safely driven lap around the simulator course with speed 30.

I further tried to use a PID control for both steering and throttle, but the twiddle optimizer just ended up with hyper parameters which caused the vehicle velocity to drop to minimum. Also using twiddling so many parameters with the simulator is very time consuming. 

So I ran the twiddle optimizer once again with only PID control for steering. As initial deltas I have chosen:
* delta_tau_p = 0.1
* delta_tau_i = 0.001
* delta_tau_d = 1.0
 
The optimizer finished with a tolerance of 0.2 and the values:
* tau_p = 2.63903
* tau_i = 0.0142273
* tau_d = 32.8519

plus a mse to reference path of **0.0152**

The mse was great, but the car movement was not desirable. These parameters basically abuse the simulator quirk, that the simulated car loses velocity whenever the steering angle is changed quickly in succession. Thus, the car "wiggles" along the reference line with 7 speed, although based on throttling parameter, it would be allowed to go at 30.
 
Maybe the mse alone is not the key for optimizing, so I added 0.5 x steering angle^2 to each mse value to prevent the above optimization from happening. This increased the mse of lesson parameters to **0.221**.
 
After another attempt to use the twiddle optimizer with the simulator, it finished with a tolerance of 0.5 and the values:
* tau_p = 2.63903
* tau_i = 0.0142273
* tau_d = 32.8519

plus a mse to reference path of **?**

These are my chosen hyper parameters.
