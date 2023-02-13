#pragma once

#include <algorithm>

namespace engine::structures
{
	enum bones : int
	{
		root = 0,

		head = 47,
		jaw = 48,
		neck = 46,

		l_hip = 1,
		l_knee = 2,
		l_foot = 3,
		l_toe = 4,
		l_ankle_scale = 5,
		
		pelvis = 6,

		r_hip = 13,
		r_knee = 14,
		r_foot = 15,
		r_toe = 16,
		
		spine1 = 18,
		spine2 = 20,
		spine3 = 21,
		spine4 = 22,
		
		l_upperarm = 24,
		l_forearm = 25,
		l_hand = 26,

		eyes = 53,

		r_upperarm = 55,
		r_forearm = 56,
		r_hand = 57,

		l_finger = 35,
		r_finger = 66
	};

	enum player_flags : int
	{
		isadmin = 4,

		sleeping = 16,
		spectating = 32,
		wounded = 64,

		connected = 256,

		thirdpersonviewmode = 1024,
		eyesviewmode = 2048,

		aiming = 16384,
	};

	struct rotator_t
	{
		float pitch;
		float yaw;
		float roll;

		rotator_t clamp( )
		{
			pitch = std::clamp( remainderf( pitch, 360.0f ), -89.0f, 89.0f );
			yaw = std::clamp( remainderf( yaw, 360.0f ), -180.0f, 180.0f );

			return { pitch, yaw };
		}

		rotator_t normalize( )
		{
			if (pitch > 180)
				pitch -= 360.0f;
			if (pitch < 180)
				pitch += 360.0f;
			if (yaw > 180)
				yaw -= 360.0f;
			if (yaw < 180)
				yaw += 360.0f;

			return { pitch, yaw };
		}

		rotator_t operator-( const rotator_t& rot ) const
		{
			return { pitch - rot.pitch, yaw - rot.yaw, roll - rot.roll };
		}

		rotator_t operator+( const rotator_t& rot ) const
		{
			return { pitch + rot.pitch, yaw + rot.yaw, roll + rot.roll };
		}

		rotator_t operator/( const float& f ) const
		{
			return { pitch / f, yaw / f, roll / f };
		}
	};

	struct quat_t
	{
		float x;
		float y;
		float z;
		float w;
	};

	struct vector2_t
	{
		float x;
		float y;

		vector2_t operator-( vector2_t value )
		{
			return { x - value.x, y - value.y };
		}

		vector2_t operator+( vector2_t value )
		{
			return { x + value.x, y + value.y };
		}

		vector2_t operator*( float value )
		{
			return { x * value, y * value };
		}

		vector2_t operator/( float value )
		{
			return { x / value, y / value };
		}

		vector2_t operator/=( float value )
		{
			x /= value;
			y /= value;

			return *this;
		}

		vector2_t operator+=( vector2_t value )
		{
			return { x += value.x, y += value.y };
		}

		vector2_t operator-=( vector2_t value )
		{
			return { x -= value.x, y -= value.y };
		}

		const float dot(const vector2_t& vec) const
		{
			return x * vec.x + y * vec.y;
		}
	};

	struct vector3_t
	{
		float x;
		float y;
		float z;

		const float dot( const vector3_t& vec ) const
		{
			return x * vec.x + y * vec.y + z * vec.z;
		}

		const float distance( vector3_t vector )
		{
			return sqrtf( powf( vector.x - x, 2.0 ) + powf( vector.y - y, 2.0 ) + powf( vector.z - z, 2.0 ) );
		}

		const float squared( ) const
		{
			return x * x + y * y + z * z;
		}

		vector3_t operator-( const vector3_t& vec ) const
		{
			return { x - vec.x, y - vec.y, z - vec.z };
		}
	};

	struct vector4_t
	{
		float x;
		float y;
		float z;
		float w;

		float color[4] = { x, y, z, w };

		const float dot( const vector3_t& vec ) const
		{
			return x * vec.x + y * vec.y + z * vec.z;
		}

		vector3_t operator-( const vector3_t& vec ) const
		{
			return { x - vec.x, y - vec.y, z - vec.z };
		}
	};

	struct matrix3x4_t
	{
		union
		{
			float matrix3x4[ 3 ][ 4 ];
		};
	};

	struct matrix4x4_t
	{
		union
		{
			float matrix4x4[ 4 ][ 4 ];
		};
	};
}