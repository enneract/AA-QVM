models/weapons/mdriver/mdriver
{
	cull disable
	{
		map models/weapons/mdriver/mdriver.jpg
		rgbGen lightingDiffuse
	}
	{
		map models/weapons/mdriver/mdriver.jpg
		blendFunc GL_SRC_ALPHA GL_ONE
		detail
		alphaGen lightingSpecular
	}
	{
		map models/buildables/mgturret/ref_map.jpg
		blendFunc GL_DST_COLOR GL_ONE
		detail
		tcGen environment
	}
	{
		map models/weapons/mdriver/mdriver_glow.tga
		blendfunc add
		rgbGen wave noise 0.2 0.5 0 3.17 
	}
	{
		map models/weapons/mdriver/mdriver_glow.tga
		blendfunc add
		rgbGen wave sawtooth 0 0.15 0 3.17 
	}
	{
		map models/weapons/mdriver/mdriver_glow.tga
		blendfunc add
		rgbGen wave sin 0.25 0.25 0 0.17 
	}
}

models/weapons/mdriver/glow
{

	cull disable
	{
		map models/weapons/mdriver/glow.jpg
		blendfunc GL_ONE GL_ONE
		tcMod scroll -9.0 9.0
	}
}
