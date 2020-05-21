#version 440

struct Material
{
	vec3 amb;
	vec3 dif;
	vec3 spec;
	sampler2D dif_tex;
	sampler2D spec_tex;

 };





in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;
out vec4 fs_color;

//uniform
uniform Material material;
uniform vec3 campos;
uniform vec3 lightPos0;

//func 
vec3 calcamb(Material material)
{
return material.amb ;
}

vec3 calcdiff(Material material, vec3 vs_position , vec3 vs_normal , vec3 lightPos0)
{
vec3 postolight = normalize(lightPos0 - vs_position);
vec3 diffcol = vec3(200.f,200.f,200.f);
float diff = clamp(dot(postolight, vs_normal),0,1);
vec3 difffin = diffcol * diff;
return vec3(1.f,1.f,1.f);
}

vec3 calcspec(Material material, vec3 vs_position , vec3 vs_normal , vec3 lightPos0 ,  vec3 campos){

vec3 lighttopos = normalize( vs_position - lightPos0 );
vec3 refl = normalize(reflect(lighttopos, normalize(vs_normal)));
vec3 postovi = normalize(campos - vs_position );
float specconst = pow(max(dot(postovi, refl),0) , 30);
vec3 specfin = material.spec *specconst;
return specfin;
}





void main(){
//fs_color = vec4(vs_color, 1.f);
//fs_color = texture(tex0,vs_texcoord) *texture(tex1,vs_texcoord) * vec4(vs_color, (1.f));

//ambient
vec3 al = calcamb(material);

//defuse 
vec3 difffin = calcdiff(material, vs_position , vs_normal, lightPos0);



//specular light 

vec3 specfin = calcspec(material, vs_position , vs_normal,lightPos0, campos);









fs_color = texture(material.dif_tex, vs_texcoord) * vec4(vs_color , 1.f)
* (vec4(specfin,1.f)+vec4(al,1.f)+ vec4(difffin,1.f));
}