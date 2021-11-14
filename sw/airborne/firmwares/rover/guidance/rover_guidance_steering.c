/* rover_steering_guidance.c */

#define AUTOPILOT_CORE_GUIDANCE_C

/** Mandatory dependencies header **/
#include "firmwares/rover/guidance/rover_guidance_steering.h"

#include "generated/airframe.h"

#include "subsystems/datalink/telemetry.h"
#include "subsystems/actuators/actuators_default.h"
#include "subsystems/radio_control.h"
#include "autopilot.h"
#include "navigation.h"
#include "state.h"

#include <math.h>
#include <stdio.h>

// Static guidance variables
static float SR_Ke = 10000.0; // TODO: config parameter in guidance_control struct 

// Guidance control main struct
rover_ctrl guidance_control;

/** Send RS guidance telemetry messages **/
static void send_msg(struct transport_tx *trans, struct link_device *dev)
{
  uint8_t ap_mode  = autopilot_get_mode();

  pprz_msg_send_STEERING_ROVER_DATA(trans, dev, AC_ID, 
                                    &ap_mode, &nav.mode, 
                                    &commands[COMMAND_THROTTLE], &commands[COMMAND_STEERING], 
                                    &actuators[SERVO_MOTOR_THROTTLE_IDX], &actuators[SERVO_MOTOR_STEERING_IDX], 
                                    &guidance_control.cmd.delta,
                                    &guidance_control.cmd.speed,
                                    &guidance_control.gvf_omega, 
                                    &guidance_control.state_speed);
}

bool rover_guidance_steering_set_delta(float delta){
  guidance_control.cmd.delta = delta;
  return true;
}

/** INIT function**/
void rover_guidance_steering_init(void)
{
  // Debugging telemetry init
  register_periodic_telemetry(DefaultPeriodic, PPRZ_MSG_ID_STEERING_ROVER_DATA, send_msg);

  guidance_control.cmd.delta = 0.0;
  guidance_control.cmd.speed = 0.0;
  guidance_control.throttle = 0.0;
}

/** PERIODIC function **/
void rover_guidance_steering_periodic(void)
{ 
  guidance_control.state_speed = stateGetHorizontalSpeedNorm_f();

  // speed is bounded to avoid GPS noise while driving at small velocity
  float delta = 0.0;
  float speed = BoundSpeed(guidance_control.state_speed); 
  float omega = guidance_control.gvf_omega;

  // ASSISTED guidance .....................................................
  if (autopilot_get_mode() == AP_MODE_ASSISTED) {
    if (fabs(omega)>0.0) {
      delta = -atanf(omega * DRIVE_SHAFT_DISTANCE / speed);
    }
    delta *= 180/M_PI;

    guidance_control.cmd.delta = BoundDelta(delta);
  }

  // NAV guidance ...........................................................
  else if (autopilot_get_mode() == AP_MODE_NAV) {
    guidance_control.cmd.delta = BoundDelta(guidance_control.cmd.delta);

    // Control speed signal
    float error = guidance_control.cmd.speed - guidance_control.state_speed;
    guidance_control.throttle = BoundThrottle(SR_Ke * error); // Simple control model...
  } 

  // FAILSAFE values ........................................................
  else {
    guidance_control.cmd.delta = 0.0;
    guidance_control.cmd.speed = 0.0;
  }

  // periodic steering_rover telemetry
  register_periodic_telemetry(DefaultPeriodic, PPRZ_MSG_ID_STEERING_ROVER_DATA, send_msg);
}




