MicroBot
====


- [Prerequisites](#Prerequisites)
- [Installation](#installation)
- [Usage](#usage)


## Prerequisites
Before you begin, you need a few things set up in your environment:

- Xcode 9.0 or later
- An Xcode project targeting iOS 10 or above
- Swift projects must use Swift 4.1 or later
- The bundle identifier of your app
- CocoaPods 1.4.0 or later
- For MicroBot:
	- A physical Gadget & iOS device
	- An Apple Push Notification Authentication Key for your Apple Developer account


## Installation

### (WIP)CocoaPods

[CocoaPods](https://cocoapods.org) is a dependency manager for Cocoa projects. You can install it with the following command:

```bash
$ gem install cocoapods
```

To integrate MicroBot into your Xcode project using CocoaPods, specify it in your `Podfile`:

```ruby
source 'https://github.com/CocoaPods/Specs.git'
platform :ios, '10.0'
use_frameworks!

target '<Your Target Name>' do
    pod 'MicroBot', '~> 0.0.1'
end
```

Then, run the following command:

```bash
$ pod install
```

### Manually
1. Download the Microbot SDK in Release directory
2. Select the project file from the project navigator on the left side of the project window.
3. Select the target for where you want to add frameworks in the project settings editor.
4. Select the “Build Phases” tab, and click the small triangle next to “Link Binary With Libraries” to view all of the frameworks in your application.
5. To Add frameworks, click the “+” below the list of frameworks.
6. To select multiple frameworks, press and hold the command key while using the mouse to click the desired frameworks.

- [Reference link](http://docs.onemobilesdk.aol.com/ios-ad-sdk/adding-frameworks-xcode.html)


## Configuration

### Configuring APNs
- Create an App ID on the [Apple Developer Member Center](https://developer.apple.com/account/) (e.g com.thenaran.microbotexample)
- Generate .p12 authenticate file.
- Upload the APNs cerification key(.p12) to MicroBot Console
- [Reference link](https://medium.com/@ankushaggarwal/generate-apns-certificate-for-ios-push-notifications-85e4a917d522)

### Configuring Capabilities in your project
- Turn on 'Uses Bluettoh LE accessories' and 'Remote notifications' In Background Modes
- Turn on Push Notifications

### Add Your Product Keys
Copy product keys from MicroBot Console & paste in your Info.plist

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>MicroBot</key>
	<dict>
		<key>ProductKeys</key>
		<dict>
			<key>mibp</key>
			<string>0cc175b9c0f1b6a831c399e269772661</string>
			<key>mibs</key>
			<string>92eb5ffee6ae2fec3ad71c777531578f</string>
		</dict>
	</dict>
</dict>
</plist>

```

## Usage

### Initialize
```swift
// Import MicroBot in your UIApplicationDelegate
import MicroBot

// Send push notification to MicroBot for handle requests from the MicroBot Cloud
func application(_ application: UIApplication, didReceiveRemoteNotification userInfo: [AnyHashable: Any],
                 fetchCompletionHandler completionHandler: @escaping (UIBackgroundFetchResult) -> Void) {
    MicroBot.shared.message.digestNotification(userInfo).done { (void) in
        completionHandler(UIBackgroundFetchResult.newData)
    }
}

// APNs token for MicroBot Cloud
func application(_ application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: Data) {
    print("APNs token retrieved: \(deviceToken)")
    MicroBot.shared.message.token = deviceToken
}

```

### Receive Events
```swift
import MicroBot

class EventReciever: MicroBotDelegate {
	init() {
		super.init()
		Microbot.shared.delegate = self
	}
	
	func mibReceivedAuthEvent(_ user: MIBUser, topic: AuthEvent, data: [String: Any]) {
		print("Recieved event from user. topic: \(topic)")  
	}
	
	func mibReceivedGadgetEvent(_ gadget: MIBGadget, topic: GadgetEvent, data: [String: Any]) 	{
	   print("Recieved event from hub. topic: \(topic)")   
	}
    
	func mibReceivedHubEvent(_ hub: MIBHub, topic: HubEvent, data: [String: Any]) {
		print("Recieved event from hub. topic: \(topic)")  
	}
	
}

```
### Authorize User
```swift
import MicroBot

class ViewController: UIViewController {

    @IBAction func selectedAuthButton(_ sender: Any) {
        if let email = self.emailTextField.text {
            // Request user authroization to MicroBot Cloud
            MicroBot.shared.auth.authorize(email).done { (resp) in
                if let userId = resp.data {
                		print("email: \(email), userId: \(userId)")
                }
            }
        }
    }
    
    // Recieve an authroization event from MicroBotDelegate
    func mibReceivedAuthEvent(_ user: MIBUser, topic: AuthEvent, data: [String: Any]) {
        print("Recieved event from user. topic: \(topic)")
        switch (topic) {
        case: .authroized:
    	      print("\(user.email) is authroized.")
        }
    }
}

```

### Scan Gadgets
```swift
class ViewController: UIViewController {
	@IBAction func selectedScanButton(_ sender: Any) {
		var scannedGadgets = [MIBGadget]()
		MicroBot.shared.gadgets.scan().done { (response) in
			if let gadget = response.data {
				scannedGadgets.append(gadget)
			}
		}
   	}
}
```

### Pair with The Gadget
```swift
import MicroBot

class ViewController: UIViewController {
    
    var scannedGadgets = [MIBGadget]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
    @IBAction func selectedScannedGadgetButton(_ sender: Any) {
		scannedGadget.pair(optSecret).done { (response) in
		if let error = response.error {
			// handle error
			}
		})
	}
      
    // Recieve a pair event from MicroBotDelegate
    func mibReceivedGadgetEvent(_ gadget: MIBGadget, topic: GadgetEvent, data: [String: Any]) {
   		switch (topic) {
   		case .paired:
   			print("Paired with new gadget: \(gadget.name)")
   		case .pairFailed 
   			print("Failed to pair with gadget: \(gadget.name)")
   		.... 
    }
}

```
### Call an Endpoint of The Gadget
```swift
import MicroBot

class ViewController: UIViewController {

	func press(_ gadget: MIBGadget, otp: Int) {
	    // Call an endpoint of Gadget 
       gadget.callEndpoint(otp, name: "press", args: 1).done { response in
           guard response.error == nil else {
				// handle error
				return
           }
           print("Push gadget is pressed")
       }
    }
}
```
