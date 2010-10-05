

static int previousRightEncoder;
static int previousLeftEncoder;











PositionChange TrackerCalculateChange(int dl, int dr)
{
	if ( dl * dr < 0 )	//	one of the values is negative
	{
		
	}
	else	//	both wheels are moving in the same direction
	{
		//	FIXME: branch if dl > dr, dr > dl?????????????
		
		float leftRadius = (dl * kRobotWidth) / (dr - d1);	//	radius from rotation point to center of left wheel
		float arcAngle = dl / leftRadius;
		float robotRadius = leftRadius + (kRobotWidth / 2);
		
		PositionChange delta;
		delta.displacement.x = robotRadius * cos(arcAngle);
		delta.displacement.y = robotRadius * sin(arcAngle);
		float dx = delta.displacement.x;
		delta.angleChange = atanf( -dx / sqrt(powf(robotRadius, 2.0) - powf(dx, 2.0)) );
	}
}


