//*! Post Frag

#version 410

in vec2 vTexCoord;

uniform sampler2D post_target;

uniform vec2 blur_factor;
uniform float distort_factor;

out vec4 FragColour;

//*! Just output the colour unchanged
vec4 Default(vec2 texCoord) 
{
	return texture( post_target, texCoord );
}


vec4 Distort(vec2 texCoord) 
{
	vec2 mid = vec2(0.5f);
	float distanceFromCentre = distance(texCoord, mid);
	vec2 normalizedCoord = normalize(texCoord - mid);
	float bias = distanceFromCentre +
	sin(distanceFromCentre * distort_factor) * 0.05f;
	vec2 newCoord = mid + bias * normalizedCoord;
	return texture(post_target, newCoord);
}
 
 // simple box blur
vec4 BoxBlur(vec2 texCoord) 
{
	//*! Blur
	vec2 texel = blur_factor / textureSize(post_target, 0);
	// 9-tap box kernel
	vec4 colour = texture(post_target, texCoord);
	colour += texture(post_target, texCoord + texel * vec2(-1,1));
	colour += texture(post_target, texCoord + texel * vec2(-1,0));
	colour += texture(post_target, texCoord + texel * vec2(-1,-1));
	colour += texture(post_target, texCoord + texel * vec2(0,1));
	colour += texture(post_target, texCoord + texel * vec2(0,-1));
	colour += texture(post_target, texCoord + texel * vec2(1,1));
	colour += texture(post_target, texCoord + texel * vec2(1,0));
	colour += texture(post_target, texCoord + texel * vec2(1,-1));
	return colour / 9;
}

vec4 Distort_Blur(vec2 texCoord)
{
	//*! Distort
	vec2 mid = vec2(0.5f);
	float distanceFromCentre = distance(texCoord, mid);
	vec2 normalizedCoord = normalize(texCoord - mid);
	float bias = distanceFromCentre +
	sin(distanceFromCentre * distort_factor) * 0.05f;
	vec2 newCoord = mid + bias * normalizedCoord;

	//*! Blur
	vec2 texel = blur_factor / textureSize(post_target, 0);
	// 9-tap box kernel
	vec4 colour = texture(post_target, newCoord);
	colour += texture(post_target, newCoord + texel * vec2(-1,1));
	colour += texture(post_target, newCoord + texel * vec2(-1,0));
	colour += texture(post_target, newCoord + texel * vec2(-1,-1));
	colour += texture(post_target, newCoord + texel * vec2(0,1));
	colour += texture(post_target, newCoord + texel * vec2(0,-1));
	colour += texture(post_target, newCoord + texel * vec2(1,1));
	colour += texture(post_target, newCoord + texel * vec2(1,0));
	colour += texture(post_target, newCoord + texel * vec2(1,-1));
	return colour / 9;
}

void main() 
{
	//*! Calculate texel size
	vec2 texSize = textureSize( post_target, 0 );
	vec2 texelSize = 1.0f / texSize;
	
	//*! Adjust texture coordinate
	vec2 scale = (texSize - texelSize) / texSize;
	vec2 texCoord = vTexCoord / scale + texelSize * 0.5f;
	
	//*! Sample post effect
	//FragColour = Default(texCoord);
 	//FragColour = Distort(texCoord);
	//FragColour = BoxBlur(texCoord);
	FragColour = Distort_Blur(texCoord);
}
