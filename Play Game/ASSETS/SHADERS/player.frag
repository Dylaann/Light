precision highp float;
uniform vec2 resolution;
uniform vec2 direction;
uniform float battery;


void main()
{
  vec3 color = vec3(0,0,0);

  vec2 midpoint = resolution.xy * 0.5;
  float dist = length(gl_FragCoord.xy - midpoint);
  float clen = 0.15;
  float cshape = min(resolution.x, resolution.y) * clen;
  float circle = smoothstep(battery, cshape, dist);

  vec2 newmid = vec2(midpoint.x + (direction.x * 2), midpoint.y + (direction.y * 2));
  float dist2 = length(gl_FragCoord.xy - newmid);
  float cshape2 = min(resolution.x, resolution.y) * clen * 1.2;
  float c2 = smoothstep(battery, cshape2, dist2);

  vec2 newmid2 = vec2(newmid.x + (direction.x * 2), newmid.y + (direction.y * 2));
  float dist3 = length(gl_FragCoord.xy - newmid2);
  float cshape3 = min(resolution.x, resolution.y) * clen * 1.4;
  float c3 = smoothstep(battery, cshape3, dist3);

  vec2 newmid3 = vec2(newmid2.x + (direction.x * 2), newmid2.y + (direction.y* 2));
  float dist4 = length(gl_FragCoord.xy - newmid3);
  float cshape4 = min(resolution.x, resolution.y) * clen * 1.6;
  float c4 = smoothstep(battery, cshape4, dist4);


  vec2 newmid4 = vec2(newmid3.x + (direction.x * 2), newmid3.y + (direction.y* 2));
  float dist5 = length(gl_FragCoord.xy - newmid4);
  float cshape5 = min(resolution.x, resolution.y) * clen * 1.8;
  float c5 = smoothstep(battery, cshape5, dist5);

  //vec2 newmid5 = vec2(newmid4.x + direction.x, newmid4.y + direction.y);
  //float dist6 = length(gl_FragCoord.xy - newmid5);
  //float cshape6 = min(resolution.x, resolution.y) * clen * 2.2;
  //float c6 = smoothstep(battery, cshape6, dist6);


  //vec2 newmid6 = vec2(newmid5.x + direction.x, newmid5.y + direction.y);
  //float dist7 = length(gl_FragCoord.xy - newmid6);
  //float cshape7 = min(resolution.x, resolution.y) * clen * 2.6;
  //float c7 = smoothstep(battery, cshape7, dist7);

  gl_FragColor = vec4(color, 0.98) * circle * c2 * c3 * c4 * c5;
}