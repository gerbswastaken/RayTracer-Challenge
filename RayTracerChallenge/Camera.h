#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"

#include <cmath>

class Camera {
	//We assume the distance between the origin from where rays are being shot from and the plane which they intersect to generate an image to be 1 unit
	public:
		int m_horizontalSizePixels = 0;
		int m_verticalSizePixels = 0;
		float m_fieldOfView = 0.0f;
		Matrix m_transformationMatrix = Matrix::createIdentityMatrix(4);
		float m_cameraHalfWidth = 0.0f;
		float m_cameraHalfHeight = 0.0f;

	private:
		float m_aspectRatio = 0.0f;
		float m_cameraHalfView = 0.0f;
		float m_cameraPixelSize = 0.0f;
		

	public:
		Camera();
		Camera(int horizontalSizePixels, int verticalSizePixels, float fieldOfView, const Matrix& transformationMatrix);

		float getCameraPixelSize() const;

};

#endif

