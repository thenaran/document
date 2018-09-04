
Introduction
===
This guide document enables you to connect Bluetooth gadgets to the MicroBot platform. It covers the API specifications, firmware and mobile kit application, and testing and deployment. The following operations are required in order to connect the devices to the MicroBot platform. All that will be required on your end is a Bluetooth gadget.

1. [Console Registration](#console)
1. [Specification Definition](#endpoint)
1. [Firmware](#firmware)
1. [Mobile App](#mobile)
1. [Test](#test)
1. [Deployment](#deploy)
1. [Update](#update)
1. [Server Connection](#3rd)

## <a name="console"></a>MicroBot Console
You can develop, test, and deploy your system on MicroBot Platform in the same infrastructure environment as Naran.

1. Visit [Console](https://console.mib.io) and sign up.
1. Firstly, register the group.![](../res/reg_org.png)
1. Register your product and code. The product name is the product name of which is served to the actual user, and the code is used to identify the product on the platform.![](../res/reg_prd.png)
1. Register your model. Models can be useful when you want to make a difference in version or function even if they are the same product. As default, at least one model must be registered per product.![](../res/reg_model.png)
1. Invite other developers of your organization.![](../res/invite.png)
	*If a member joins directly from the console rather than from an invitation, they will belong to the new organization.*

## <a name="endpoint"></a>Endpoint Specific3ation
Endpoint Specification defines the endpoints and events that the gadget needs to work with. Through the defined statement, MicroBot Platform calls the gadget endpoint and forwards the event to the user's other hub.

1. Firstly, define the gadget endpoint and the event. [Link](https://github.com/thenaran/document/blob/master/microbot-nrf/README.md#define-endpoints-or-events-on-microbotcloud)
1. Upload the created specification on [Console](https://console.mib.io) and register.![](../res/spec_upload.png)

## <a name="firmware"></a>Firmware
1. Download the generated gadget header and apply it to the firmware. [Link](https://github.com/thenaran/document/blob/master/microbot-nrf/README.md)	![](../res/spec_down.png)
1. Apply the firmware to the model.![](../res/model_firmware.png)

## <a name="mobile"></a>Mobile App
Create a mobile application that controls the MicroBot SDK applied gadgets. Likewise, build your application through the platform SDK.
### iOS
* [Getting started for Swift](https://github.com/thenaran/document/blob/master/microbot-swift/README.md)

#### Sample App for iOS
* Without creating a separate mobile application, you can check basic operation through the sample app.

### Android
* Kotlin: WIP

## <a name="test"></a>Test
It is possible to control and verify your gadget directly through your mobile application. However, you can test endpoints and events more easily and quickly through the specifications defined through the [Console](https://console.mib.io)

1. Add the user to test first.
![](../res/invite_tester.png)
	* If necessary, you can try out the Pre Release version by adding an external tester.
1. Prepare the MicroBot SDK applied gadgets and mobile applications.
1. In the [Console](https://console.mib.io), go to the Endpoint test page.
1. Press the test button to check the function. ![](../res/spec_test.png)
1. Change the version you are developing to the Pre Release stage.(see [Deployment](#deploy))

## <a name="deploy"></a>Deployment
You can check each stage before releasing the product in development.

* Release: The version currently in service to the user.
* Pre Release: This is a version that can be tested before the release.
* Dev: This is the current version in development.
* Archive: When a new version is released, the old version will be stored here.
![](../res/stage.png)

## <a name="update"></a>Update
1. If necessary, register a new specification.
1. Upload a new firmware file to the model. Once the new firmware is registered, the API is provided so that the mobile SDK can update the firmware of the user's gadget.
1. It can be deployed to other stages through the Release menu and it can be tested or provided to users.

## <a name="3rd"></a>External Server Connection
If you are running a separate server, you can control the gadget through the API provided by MicroBot Cloud.

* [Getting started for 3rd Party](https://github.com/thenaran/document/blob/master/microbot-cloud/3rdapis.md)