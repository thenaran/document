# MIBCloud 3rdparty Getting started

## Rest API reference
### Overview
URIs relative to https://a.prota.space/v1, unless otherwise noted

#### Authorization

Need to request with an access token. it is presented in https://console.mib.io

Example:

* curl
```http
$ curl '{REST_API_URL}' -i -H 'Authorization: Bearer {access_token}'
```

#### Request

Only supports a json format.

#### Response

Return value type is a json format.

#### How to request a endpoint and get a result

1. Choice a gadget to request an endpoint. you can get gadget list by "**/products/{product_id}/gadgets**"
2. Requests an endpoint by "**/gadgets/{gadget_id}/endpoints/{command}**". It will run an endpoint with async process. you can get a task ID as the return value. It is used to retrieve a return value of an endpoint.
3. Get a return value by "**/gadgets/{gadget_id}/results/{task_id}**". You can get a return value.

#### Reserved Task code

| Code | Description |
| --- | --- |
| 0 | Success |
| 1 | Failed |
| 124 | Timeout |

### APIs
#### Users
##### **Gets a user's data by email.**
HTTP Request

```http
GET https://a.prota.space/v1/users/{email}
```

Parameters

* Path paramters

| Parameter name | description |
| --- | --- |
| email | User's email address registered in the MIBcloud |

Request Header

* Authorization: Bearer {access_token}

Request body

* Do not supply a request body with this method.

Response

* HTTP CODE: 200
  * It is success
  * Headers
    * Content-Type: application/json
  * Body
```json
{"id": "(string) The ID for user registered in the MIBcloud",
 "email": "(string) User's email address registered in the MIBcloud",
 "language": "(string) Default language code of user",
 "account_ids": ["(string) The IDs associated with user", ]}
```
* HTTP CODE: 400
  * Need to checks arguments
* HTTP CODE: 401
  * Need to checks an access token
* HTTP CODE: 404
  * Need to check an url
* HTTP CODE: 405
  * Need to check a request method
* HTTP CODE: 500
  * Occurs an error from a server

Example

* cURL

```http
$ curl 'https://a.prota.space/v1/users/{email}' -i -H 'Authorization: Bearer {access_token}'
```

#### Products
##### Gets gadgets data of a product by product id
HTTP Request

```http
GET https://a.prota.space/v1/products/{product_id}/gadgets
```

Parameters

* Path paramters

| Parameter name | description |
| --- | --- |
| product_id | Product ID to get gadgets |

Request Header

* Authorization: Bearer {access_token}

Request body

* Do not supply a request body with this method.

Response

* HTTP CODE: 200
  * It is success
  * Headers
    * Content-Type: application/json
  * Body
```json
[{"id": "(string) The generaged gadget ID",
 "mac": "(string) MAC address of a gadget",
 "name": "(string) Default name of a gadget",
 "kind": "(string) Product ID of a gadget",
 "firmware_version": "(string) Firmware version of a gadget",
 "sdk_version": "(string) Compiled sdk version of a gadget ",
 "model_number": "(integer) Model number of a gadget",
 "model_name": "(string) Model name of a gadget",
 "hub_id": "(string) The IDs associated with a hub",
 "account_id": "(string) The IDs associated with an account",
 "user_id": "(string) The IDs associated with an user",
 "status": "(integer) status code number of a gadget",
 "rssi": "(integer) RSSI of a gadget with a hub",
 "battery": "(integer) Battery level of a gadget"
 },
 ...
]
```
* HTTP CODE: 400
  * Need to checks arguments
* HTTP CODE: 401
  * Need to checks an access token
* HTTP CODE: 403
  * No permission for a specified gadget
* HTTP CODE: 404
  * Need to check an url
* HTTP CODE: 405
  * Need to check a request method
* HTTP CODE: 500
  * Occurs an error from a server

Example

* cURL

```http
$ curl 'https://a.prota.space/v1/products/{product_id}/gadgets' -i -H 'Authorization: Bearer {access_token}'
```

#### Gadgets
##### Call an endpoint to gadget
HTTP Request

```http
POST https://a.prota.space/v1/gadgets/{gadget_id}/endpoints/{command}
```

Parameters

* Path paramters

| Parameter name | description |
| --- | --- |
| gadget_id | Gadget ID to call an endpoint |
| command | An endpoint command |

Request Header

* Authorization: Bearer {access_token}

Request body

* Type: application/json

```json
{"args": ["(any) Argumnets of endpoint"],
 "kwargs": {"(string) argument key": "(any) argument value"},
 "key": "(string) Product key of a gadget product",
 "otp": "(integer) (optional) Generated a otp number by salt"
}
```

Response

* HTTP CODE: 200
  * It is success
  * Headers
    * Content-Type: application/json
  * Body
```json
{"task_id": "(integer) Task ID to get a result of an endpoint request"}
```
* HTTP CODE: 400
  * Need to checks arguments
* HTTP CODE: 401
  * Need to checks an access token
* HTTP CODE: 403
  * No permission for a specified gadget
* HTTP CODE: 404
  * Need to check an url
* HTTP CODE: 405
  * Need to check a request method
* HTTP CODE: 500
  * Occurs an error from a server

Example

* cURL

```http
$ curl -X POST "https://a.prota.space/v1/gadgets/{gadget_id}/endpoints/{command}" -i -H "Authorization: Bearer {access_token}" -H "Content-Type: application/json" -d '{"args": {args}, "kwargs": {kwargs}}'
```

##### Get an endpoint result of a gadget
HTTP Request

```http
GET https://a.prota.space/v1/gadgets/{gadget_id}/results/{task_id}
```

Parameters

* Path paramters

| Parameter name | description |
| --- | --- |
| gadget_id | Gadget ID to get an result |
| task_id | Task ID to get when it requested an endpoint |

Request Header

* Authorization: Bearer {access_token}

Request body

* Do not supply a request body with this method.

Response

* HTTP CODE: 200
  * It is success
  * Headers
    * Content-Type: application/json
  * Body
```json
{"code": "(integer) return code of a spcified task",
 "value": {"otp": "(integer) otp number of a return value issuer. it is optional",
           "value": "(any) return value of a task""}
 }
```
* HTTP CODE: 400
  * Need to checks arguments
* HTTP CODE: 401
  * Need to checks an access token
* HTTP CODE: 403
  * No permission for a specified task
* HTTP CODE: 404
  * Need to check an url
* HTTP CODE: 405
  * Need to check a request method
* HTTP CODE: 500
  * Occurs an error from a server

Example

* cURL

```http
$ curl -X GET "https://a.prota.space/v1/gadgets/{gadget_id}/results/{task_id}" -i -H "Authorization: Bearer {access_token}"
```

##### Notify a message to a hub associated with a gadget
HTTP Request

```http
POST https://a.prota.space/v1/gadgets/{gadget_id}/message
```

Parameters

* Path paramters

| Parameter name | description |
| --- | --- |
| gadget_id | Gadget ID to send a message |

Request Header

* Authorization: Bearer {access_token}

Request body

* Type: application/json

```json
{"title": "(string) Title of message",
 "body": "(string) Message",
 "all": "(boolean) If true, send a message to all owned hubs of user"
}
```

Response

* HTTP CODE: 200
  * It is success
  * Headers
    * Content-Type: application/json
  * Body
```json
{"value": "(boolean) True, it is success."}
```
* HTTP CODE: 400
  * Need to checks arguments
* HTTP CODE: 401
  * Need to checks an access token
* HTTP CODE: 403
  * No permission for a specified gadget
* HTTP CODE: 404
  * Need to check an url
* HTTP CODE: 405
  * Need to check a request method
* HTTP CODE: 500
  * Occurs an error from a server

Example

* cURL

```http
$ curl -X POST "https://a.prota.space/v1/gadgets/{gadget_id}/message" -i -H "Authorization: Bearer {access_token}" -H "Content-Type: application/json" -d '{"title": {title}, "body": {messages}}'
```

##### Publish an event to related hubs
HTTP Request

```http
POST https://a.prota.space/v1/gadgets/{gadget_id}/event
```

Parameters

* Path paramters

| Parameter name | description |
| --- | --- |
| gadget_id | Gadget ID to send a message |

Request Header

* Authorization: Bearer {access_token}

Request body

* Type: application/json

```json
{"topic": "(string) Specified topic name of event",
 "value": "(any) Event value"
}
```

Response

* HTTP CODE: 200
  * It is success
  * Headers
    * Content-Type: application/json
  * Body
```json
{"value": "(boolean) True, it is success."}
```
* HTTP CODE: 400
  * Need to checks arguments
* HTTP CODE: 401
  * Need to checks an access token
* HTTP CODE: 403
  * No permission for a specified gadget
* HTTP CODE: 404
  * Need to check an url
* HTTP CODE: 405
  * Need to check a request method
* HTTP CODE: 500
  * Occurs an error from a server

Example

* cURL

```http
$ curl -X POST "https://a.prota.space/v1/gadgets/{gadget_id}/event" -i -H "Authorization: Bearer {access_token}" -H "Content-Type: application/json" -d '{"topic": {topic}, "value": {value}}'
```

### Events
#### Overview

If register a hook url, product related all events are delivered to a hook url with POST method.

Event values have many common forms. Please refer to a common value item.

| type | value |
| --- | --- |
| method | POST |
| url | {registered hook url} |
| header | Authorization: Bearer {registered hook client key} |
| | Content-type: application/json |
| body | ```{"gadget_id": {gadget_id}, "topic": {event_topic}, "value": {event_value}``` |

##### Common Values
* GADGET DATA

```json
{"id": "(string) The generaged gadget ID",
 "mac": "(string) MAC address of a gadget",
 "name": "(string) Default name of a gadget",
 "kind": "(string) Product ID of a gadget",
 "firmware_version": "(string) Firmware version of a gadget",
 "sdk_version": "(string) Compiled sdk version of a gadget ",
 "model_number": "(integer) Model number of a gadget",
 "model_name": "(string) Model name of a gadget",
 "hub_id": "(string) The IDs associated with a hub",
 "account_id": "(string) The IDs associated with an account",
 "user_id": "(string) The IDs associated with an user",
 "status": "(integer) status code number of a gadget",
 "rssi": "(integer) RSSI of a gadget with a hub",
 "battery": "(integer) Battery level of a gadget"
 }
```

#### Common Topics
* Paired a gadget
```json
{"gadget_id": "(string) topic issuer",
 "topic": "gadget.paired",
 "value": "{GADGET DATA}"
}
```

* Connected a gadget with a hub
```json
{"gadget_id": "(string) topic issuer",
 "topic": "gadget.connected",
 "value": "{GADGET DATA}"
}
```

* Disonnected a gadget from a hub
```json
{"gadget_id": "(string) topic issuer",
 "topic": "gadget.disconnected",
 "value": "{GADGET DATA}"
}
```

* Unpaired a gadget
```json
{"gadget_id": "(string) topic issuer",
 "topic": "gadget.unpaired",
 "value": "{GADGET DATA}"
}
```
