# Discussion

## Imaging Parameters Optimization

If all you wanted to do was to maximize the signal-to-noise ratio (SNR) of your images, then you would increase the exposure time and/or light intensity until the histogram was as far to the right of its range as possible without saturating any pixels.

But what if the intensity is maxed out and you still have room left in the histogram to improve the SNR? You could increase the exposure time still further. But, as a result, doing so would decrease your frame rate. If you also needed to image fast dynamics within the cell, then there would be an upper limit to the value for the exposure time that you can set. Beyond this value, you would not have a high enough frame rate to see the thing that you would like to see; it would be blurred out.

Ultimately this means that you must sacrifice some SNR to obtain a sufficient temporal resolution. We can visualize the problem like this:

![](./snr_frame_rate_vs_exposure_time.png)

Do not worry too much about the exact shapes of the curves in the sketch above; what's important are the trends. SNR increases with exposure time, whereas frame rate decreases. The dynamics that you want to see set a requirement on the minimum frame rate at which you can image. You can imagine this minimum as follows:

![](./minimum_frame_rate.png)

But the minimum frame rate imposes a maximum on the exposure time. This value is just the vertical line through the point of intersection of the frame rate curve and its minimum required value.

Taking this logic one step further, the maximum exposure time also imposes a maximum achieveable SNR, so in the end we have something like this:

![](./maximum_snr.png)

The frame rate requirement ends up reducing the parameter space of exposure time and, subsequently, the maximum achieveable SNR.

We have finally arrived at an optimization problem: given the frame rate requirement, what exposure time maximizes SNR?

The answer in this case is straightforward: it's the exposure time that corresponds to the value where the frame rate is *just* fast enough to see the dynamics that you are after.

![](./optimum.png)

You can of course image at shorter exposure times, but then your SNR will suffer, and there is never a benefit to having images with less SNR.

## What Parameter Values should I choose?

The above discussion is fine from a theoretical perspective. But you're probably wondering how to set the actual value of the exposure time when at the microscope.

This is where imaging becomes a bit more art than science. For one, you can estimate the SNR by using the image histograms. A good SNR means the histogram center is as far to the right of its range as possible without saturating pixels. But keep in mind that this is not the same as measuring the SNR directly.

And what sets the minimum frame rate? Here pilot experiments can help. You can try a range of exposure times and frame intervals on test samples and see roughly what range of values works. You may not arrive at exact values, but you can at least establish a rough order of magnitude.

Back of the envelope calculations help to pinpoint ranges of parameter values in some scenarios. For example, in tracking experiments, if you know the density of particles and their diffusion constants, then you can work out what frame rate is necessary to capture a certain number of frames before a collision occurs with another particle.

## What Else can I Adjust in my Experiments?

It's not only microscope parameters that can be tuned. Signal-to-background ratio, for example, can be improved through better sample preparation or a change of microscope. For example, a switch from widefield to confocal can help in this scenario. The key is to identify what aspect of the imaging process is preventing you from answering your hypotheses.

## What about Photobleaching, Phototoxicity, and Spatial Resolution?

I deliberately left these out of the discussion above to keep it simple, but they need to be considered as well. Phototoxicity and photobleaching ultimately limit the laser intensity (which limits the SNR) and the length of your experiments. You won't be able to avoid these effects entirely.

Spatial resolution is harder to adjust through microscope parameters alone since it depends heavily on the microscopy method itself. Still, improving SNR does slightly improve spatial resolution, and choice of microscope is just as important as anything else when designing an imaging experiment.

**The key is to establish the requirements for your experiments in terms of these properties:**

- spatial resolution
- temporal resolution
- SNR
- phototoxicity

**and these constraints:**

- budget
- time available
- equipment available
- expertise

 Without any requirements or constraints, there is no way of doing meaningful, quantitative experiments on a microscope.

## Polyhedrons of Feeling

You might have heard of the "triangle of frustration", "pyramid of compromise," or similar terms. One such example looks like this ([source](https://academic.oup.com/biomethods/article/9/1/bpae075/7818344)):

![](./triangle_of_frustration.png)

The idea here is that you can move about within the pyramid by adjusting imaging parameters, the microscopy method, the sample prep, and more. In doing so, you improve on one of the qualities at the vertexes of the pyramid but necessarily sacrifice something at the other vertexes. Improving spatial resolution, for example, might mean decreasing temporal resolution and cell health.

Again, it's very hard to put the imaging problem on firm, algorithmic grounds with definite data. This is partly because we can't measure everything we need to (how do you quantify phototoxicity?), partly because it's not always clear what makes for an optimum set of parameter values. Still, these concepts help you navigate the challenges inherent in optimizing your imaging experiments by

1. making clear what the tradeoffs are, and
2. helping design pilot experiments that help narrow in on the right range of microscope parameter values.
