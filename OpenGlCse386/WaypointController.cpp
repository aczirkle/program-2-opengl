#include "WaypointController.h"


WaypointController::WaypointController( vector<vec3> points, GLfloat spd  )
	:speed(spd), waypoints(points), position(waypoints[0]), targetWaypointIndex(0), velocity(vec3(0))
{ 
	updateVeolcityForNewWaypoint();

} // end constructor
 

void WaypointController::update(float elapsedTimeSeconds)
{
	GLfloat distance = distanceToTargetWaypoint();

	static bool firstUpdateComplete = false;

	if ( distance < (speed * elapsedTimeSeconds) ) {
		position = waypoints[targetWaypointIndex];
		updateVeolcityForNewWaypoint();
	}
	if (!firstUpdateComplete ){

		elapsedTimeSeconds = 0.0;
		firstUpdateComplete = true;

	}

	position = position + velocity * elapsedTimeSeconds;
	target->modelMatrix = translate(mat4(1.0f), position);

} // end update


int WaypointController::getNexWaypointIndex()
{
	return (targetWaypointIndex+1)% waypoints.size();

} // end getNexWaypointIndex


void WaypointController::updateVeolcityForNewWaypoint()
{
	targetWaypointIndex = getNexWaypointIndex();

	velocity = (waypoints[targetWaypointIndex] - position);
	velocity = normalize(velocity);
	velocity *= speed;

} // end updateVeolcityForNewWaypoint


GLfloat WaypointController::distanceToTargetWaypoint()
{
	return length(waypoints[targetWaypointIndex] - position);

} // end distanceToTargetWaypoint