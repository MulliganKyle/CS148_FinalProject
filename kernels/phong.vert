varying vec3 eyeSpaceNormal;
varying vec3 eyeSpaceViewDir;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
   eyeSpaceNormal = gl_NormalMatrix * gl_Normal;
   eyeSpaceViewDir= (gl_ModelViewMatrix * gl_Vertex).xyz * vec3(1,1,-1);
}
