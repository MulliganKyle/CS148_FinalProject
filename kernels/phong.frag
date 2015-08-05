varying vec3 eyeSpaceNormal;
varying vec3 eyeSpaceViewDir;
vec3 lightDir = vec3( 0.0, 0.0, 1.0);

vec3 ambientColor= vec3(0.0,0.0,0.25);
vec3 diffuseColor= vec3(0.0,0.0,0.5);
vec3 specularColor= vec3(1.0,1.0,1.0);
vec3 lightColor= vec3(1.0,1.0,1.0);
float shinyness = 50.0;

vec4 blinnPhong(vec3 N, vec3 L, vec3 V)
{
   vec3 H= normalize(L+V);
   vec3 amb = ambientColor*lightColor;
   vec3 diff = diffuseColor * dot(L,N) * lightColor;
   vec3 spec = specularColor * pow(dot(H,N), shinyness) * lightColor;

   spec = max(spec, vec3(0,0,0));
   return vec4(amb + diff + spec, 1.0);
}


void main(void)
{
   vec3 N = normalize(eyeSpaceNormal);
   vec3 L = normalize(lightDir);
   vec3 V = normalize(eyeSpaceViewDir);

   gl_FragColor = blinnPhong(N, L, V);
}
