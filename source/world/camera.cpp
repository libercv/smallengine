
#include "camera.h"

namespace Small
{
	void Camera::Render(void)
	{
		// PENDIENTE: aquí haremos Drawing3D::Instance().DrawCamera(this, 50); para quitarnos todo el código OpenGL de enmedio
		glPushMatrix();
			glTranslatef(Position.x,Position.y,Position.z);
			// PENDIENTE: BillboardXYZ solo tiene que actualizar las rotaciones. Aquí habrá que hacer 3 GlRotates(), uno por eje.
			BillboardXYZ(View);
			Drawing3D::Instance().DrawCamera(50);
		glPopMatrix();
	};

	void Camera::Apply(void)
	{
		// PENDIENTE: el upVector ¿ será siempre (0,1,0) ? ¡¡ NO !!
		gluLookAt(Position.x,Position.y,Position.z,  View.x,View.y,View.z,  0.0f,1.0f,0.0f);
	}

	void Camera::RotateView(int dx, int dy)
	{
		static float currentRotX = 0.0f;
		float prevRotX;

		float angleY = 0.0f;
		float angleZ = 0.0f;

		// PENDIENTE: Esta función se puede simplificar un pelín.

		// PENDIENTE: sustituir 100.0f por una sensibilidad configurable
		angleY = ( (float)(dx) ) / 100.0f;
		angleZ = ( (float)(dy) ) / 100.0f;
		
 		prevRotX = currentRotX;
		
		currentRotX += angleZ;

		if(currentRotX > 1.0f)     
		{
			currentRotX = 1.0f;
			
			if(prevRotX != 1.0f) 
			{
				Vector3d vAux,vAxis;
				Vector3d vUp(0,1,0);

				View.Subtract(Position, vAux);
				vAxis = vAux.CrossProduct(vUp);
				vAxis.Normalize();
					
				// PENDIENTE: pasar un vector3d & a RotateView
				RotateView( 1.0f - prevRotX, vAxis.x, vAxis.y, vAxis.z);
			}
		}
		else if(currentRotX < -1.0f)
		{
			currentRotX = -1.0f;
			
			if(prevRotX != -1.0f)
			{
				Vector3d vAux,vAxis;
				Vector3d vUp(0,1,0);

				View.Subtract(Position, vAux);
				vAxis = vAux.CrossProduct(vUp);
				vAxis.Normalize();
				
				RotateView( -1.0f - prevRotX, vAxis.x, vAxis.y, vAxis.z);
			}
		}
		else 
		{	
			Vector3d vAux,vAxis;
			Vector3d vUp(0,1,0);

			View.Subtract(Position,vAux);
			vAxis = vAux.CrossProduct(vUp);
			vAxis.Normalize();
		
			RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
		}

		RotateView(angleY, 0, 1, 0);
	}

	void Camera::RotateView(float angle, float x, float y, float z)
	{
		Vector3d vNewView, vView;

		float cosTheta = (float)cos(angle);
		float sinTheta = (float)sin(angle);

		View.Subtract(Position, vView);

		vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
		vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
		vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;

		vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
		vNewView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
		vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;

		vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
		vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
		vNewView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;

		View.x = Position.x + vNewView.x;
		View.y = Position.y + vNewView.y;
		View.z = Position.z + vNewView.z;
	}
} // namespace Small
