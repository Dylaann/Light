uniform float time;
uniform vec2  pos;

void main(void){
	vec2 p = (gl_FragCoord.xy - pos) / 500;

	float l = 0.1 * abs(sin(time)) / length(p);

	gl_FragColor = vec4(vec3(l / 2), 1.0);
}