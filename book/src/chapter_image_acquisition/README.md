# Image Acquisition

In this chapter we begin construction of a custom-built microscope for epifluorescence and transillumination imaging of cell culture samples.

We begin by explaining the basic components of a microscope and their layout. Then, we start the practical work by interfacing our microscope's camera with the computer, installing the necessary drivers and capture software. As you will see, a working camera will be essential for aligning the microscope's optical components.

Following this, we assemble our camera and tube lens into a simple, fixed focal length imaging system for imaging far away objects. We will align the camera and lens such that objects at infinity[^1] will be imaged onto the camera.

Finally, we set up [Micro-Manager](https://micro-manager.org/) to control our camera. Using Micro-Manager will allow us to design and execute complex microscopy acquisitions that we otherwise could not do with the camera's capture software.

[^1]: The meaning of this phrase will be explained later in this chapter. For now, you can think of it as meaning objects that are far away.
