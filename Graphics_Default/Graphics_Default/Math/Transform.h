#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<glm.hpp>
#include<gtx/transform.hpp>

struct Transform
{
public:
	//Components:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	//Constructor:
	/// <summary>Scale will default to [1,1,1]. Position and Rotation will default to [0,0,0].</summary>
	Transform() : position(glm::vec3(0,0,0)) , rotation(glm::vec3(0,0,0)), scale(glm::vec3(1,1,1)) {};
	/// <param name="p :">Position</param> <param name="r :">Rotation</param><param name="s :">Scale</param>
	Transform(glm::vec3 p, glm::vec3 r, glm::vec3 s) : position(p), rotation(r), scale(s) {};
	
	//Deconstructor:
	~Transform();

	//Methods:
	/// <summary>Returns a matrix using the context of each component.</summary>
	inline glm::mat4 GetMatrix() const
	{
		//Convert transform components to matricies:
		glm::mat4 posMatrix = glm::translate(position);

		//Calculate a matrix for each component of the three vector rotation.
		glm::mat4 rotXMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(scale);

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		//Return a matrix using the result of each vectors matrix.
		return posMatrix * rotMatrix * scaleMatrix;
	}
};
#endif //!TRANSFORM_H