#include "Material.h"

Material::Material()
{

}

Material::~Material()
{

}

void Material::Update()
{

}

void Material::SetBase(Texture* texture) { base = texture; }
void Material::SetNormal(Texture* texture) { normal = texture; }

void Material::SetShader(Shader* shader) { this->shader = shader; }
