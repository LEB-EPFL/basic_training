# The Epifluorescence Microscope

Microscopes come in many different shapes, sizes, and arrangements. Broadly speaking, we may classify a microscope according to two different characteristics:

1. The contrast mechanism
2. The probe

Contrast refers to the variations of intensity within an image. Higher contrast means a greater degree of these variations, which is almost always desirable for seeing small features. We can refine this definition and go into much greater detail about what contrast means for different types of microscopes, but this would distract from our main purpose at this point, which is learning about practical microscopy.

Contrast mechanism is the physical process by which variations in intensity are generated in a microscope image. It can be either intrinsic, such as the absorption and scattering of light or other types of radiation from the sample itself, or extrinsic, such as fluorescent labels that we attach to our samples.

In nearly all forms of microscopy we need to probe our samples in order to see them. In atomic force microscopy, for example, we bring a sharp tip close to a sample's surface to measure its height profile. In this case the probe is a very real and tangible thing. Most forms of microscopy, however, use directed beams of radiation such as light or electrons as the probe. The interaction between the radiation and the sample is ultimately what creates contrast in the image.

Light microscopy in particular refers to all forms of microscopy that use visible and near infrared light as the probe. It is probably the form of microscopy that is most used by cell biologists because light is relatively easy to manipulate and can generate very detailed images of cells with good contrast. It is also comparatively gentle on samples, enabling live cell time lapse imaging for long periods of time.

Typically there are two ways to deliver light to the sample. One is to stick the sample directly between a light source and the microscope to record the light signal that is transmitted through the sample. This geometry is called transillumination and is almost always used to probe a sample's intrinsic contrast. The other is to illuminate and collect light from the sample through the same optical elements. This is called epi-illumination, and nearly all flourescence microscopes use it because it is much easier to separate the probe light from the fluorscence signal than it is in transillumination.

In this course you will construct and operate what is known as an epifluorescence microscope, i.e. a light microscope that illuminates the sample by epi-illumination and uses fluorescence as the extrinsic contrast mechanism.

## Principle Components of an Epifluorescence Microscope

The diagram below illustrates the layout of a typical epifluorescence microscope.

![Layout of an epifluorescence microscope](epifluorescence-microscope.svg)

You can see right away that there are two distinct, partially overlapping light paths, and the components of this microscope are positioned relative to these two paths.

### The Illumination Light Path

The illumination path delivers excitation light to the sample. It is called excitation light because this light excites the flourophores to a higher energetic state, often called an excited state. The fluorophores will in turn emit fluorescence light when they relax from the excited state to the ground state.

The illumination path starts at the light source, which can be a LED, a laser, a lamp, or any other bright source of visible light. A series of optics directs this light through an excitation filter. The excitation filter absorbs light with wavelengths that are outside of the filter's passband and transmits light with wavelengths that are inside the passband. The purpose of the excitation filter is to narrow the spectrum of the light that eventually reaches the sample. By narrowing the spectrum, we

1. reduce any unwanted background signal that might leak towards the camera, and 
2. can better control which fluorophores are excited in the case of multi-color imaging.

Next, the light is redirected by a dichroic mirror that reflects light of some wavelengths and transmits others. The excitation light then passes through the objective lens where it is focused onto the sample to the excite fluorescence.

### The Fluorescence Light Path

Fluorescence light is collected from the sample by the objective where it traverses the illumination light path in reverse. Fluorescence light has a longer wavelength than the excitation light, so it passes through the dichroic mirror instead of reflecting. An emission filter further helps remove any residual excitation light that might be traveling along this path. A normal mirror redirects the light into a different direction, though this is not necessary and is used only to reduce the overall size of the microscope.

Finally, a tube lens collects the fluorescent light and forms the image of the sample on the camera.
