#include "Camera.h"

Camera::Camera() {
	//Nothing in here
}

Camera::Camera(int horizontalSizePixels, int verticalSizePixels, float fieldOfView, const Matrix& transformationMatrix) {
	m_horizontalSizePixels = horizontalSizePixels;
	m_verticalSizePixels = verticalSizePixels;
	m_fieldOfView = fieldOfView;
	m_transformationMatrix = transformationMatrix;

	//Now to figure out pixel size...
	m_cameraHalfView = tan(m_fieldOfView / 2.0f);
	m_aspectRatio = (float)m_horizontalSizePixels / (float)m_verticalSizePixels;

	if (m_aspectRatio >= 1) {	//Horizontal is longer than Vertical 
		m_cameraHalfWidth = m_cameraHalfView;
		m_cameraHalfHeight = m_cameraHalfWidth / m_aspectRatio;
	}
	else {	//Vertical is longer than Horizontal
		m_cameraHalfWidth = m_cameraHalfView * m_aspectRatio;
		m_cameraHalfHeight = m_cameraHalfView;
	}

	m_cameraPixelSize = (m_cameraHalfWidth * 2.0f) / ((float)m_horizontalSizePixels) ;

}

float Camera::getCameraPixelSize() const {
	return m_cameraPixelSize;
}