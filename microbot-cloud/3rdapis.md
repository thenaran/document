# MIBCloud 3rdparty Getting started

## Rest API reference
### Overview
URIs relative to https://a.prota.space/v1, unless otherwise noted

#### Authorization

Need to request with an access token. it is presented in https://console.microbot.is.

Example:

* curl
```http
$ curl '{REST_API_URL}' -i -H 'Authorization: Bearer {access_token}'
```

#### Request

Only supports a json format.

#### Response

Return value type is a json format.

### APIs
#### Users
##### **Gets a user's data by email.**
HTTP Request

```http
GET https://a.prota.space/v1/users/{email}
```

Parameters

* Path paramters

| Parameter name | value | description |
| --- | --- | --- |
| email | string | User's email address registered in the MIBcloud |

Request body

* Do not supply a request body with this method.

Response

* Type: application/json

| key | value | description |
| --- | --- | --- |
| id | string | The ID for user registered in the MIBcloud |
| email | string | User's email address registered in the MIBcloud |
| language | string | Default language code of user |
| account_ids | string list | The IDs associated with user |

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

| Parameter name | value | description |
| --- | --- | --- |
| product_id | string | Product ID to get gadgets |

Request body

* Do not supply a request body with this method.

Response

* Type: application/json

| key | value | description |
| --- | --- | --- |
| id | string | The generaged gadget ID |
| mac | string | MAC address of a gadget |
| name | string | Default name of a gadget |
| kind | string | Product ID of a gadget |
| firmware_version | string | Firmware version of a gadget |
| sdk_version | string | Compiled sdk version of a gadget |
| model_number | integer | Model number of a gadget |
| model_name | string | Model name of a gadget |
| hub_id | string | The IDs associated with a hub |
| account_id | string | The IDs associated with an account |
| user_id | string | The IDs associated with an user |
| status | integer | status code number of a gadget |
| rssi | integer | RSSI of a gadget with a hub |
| battery | integer | Battery level of a gadget |

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to call an endpoint |
| command | string | An endpoint commandP |

Request body

* Type: application/json

| key | value | description |
| --- | --- | --- |
| args | list | Arguments of endpoint |
| kwargs | dictionary | Key arguments of endpoint |
| key | string | Product key of a gadget product |
| otp | interger | (optional) Generated a otp number by salt |

Response

* Type: application/x-www-form-urlencoded

| value type | description |
| --- | --- |
| string | Task ID to get a result of an endpoint request |

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to get an result |
| tast_id | string | Task ID to get when it requested an endpoint |

Request body

* Do not supply a request body with this method.

Response

* Endpoint returned value

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to send a message |

Request body

* Type: application/json

| key | value | description |
| --- | --- | --- |
| title | string | Title of message |
| body | string | Messages |

Response

* True if requests is successed

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to send a message |

Request body

* Type: application/json

| key | value | description |
| --- | --- | --- |
| topic | string | Specified topic name of event |
| value | any | event value |

Response

* True if requests is successed

Example

* cURL

```http
$ curl -X POST "https://a.prota.space/v1/gadgets/{gadget_id}/event" -i -H "Authorization: Bearer {access_token}" -H "Content-Type: application/json" -d '{"topic": {topic}, "value": {value}}'
```

### Events
#### Overview

If register a hook url, product related all events are delivered to a hook url with POST method.

| type | value |
| --- | --- |
| method | POST |
| url | {registered hook url} |
| header | Authorization: Bearer {registered client key} |
| | Content-type: application/json |
| body | ```{"gadget_id": {gadget_id}, "topic": {event_topic}, "value": {event_value}``` |

#### Topics
* Paired a gadget to hub
| key | value |
| --- | --- |
| gadget_id | topic issuer |
| topic | gadget.paired |
| value | {GADGET DATA} |
* GADGET DATA
# MIBCloud 3rdparty Getting started

## Rest API reference
### Overview
URIs relative to https://a.prota.space/v1, unless otherwise noted

#### Authorization

Need to request with an access token. it is presented in https://console.microbot.is.

Example:

* curl
```http
$ curl '{REST_API_URL}' -i -H 'Authorization: Bearer {access_token}'
```

#### Request

Only supports a json format.

#### Response

Return value type is a json format.

### APIs
#### Users
##### **Gets a user's data by email.**
HTTP Request

```http
GET https://a.prota.space/v1/users/{email}
```

Parameters

* Path paramters

| Parameter name | value | description |
| --- | --- | --- |
| email | string | User's email address registered in the MIBcloud |

Request body

* Do not supply a request body with this method.

Response

* Type: application/json

| key | value | description |
| --- | --- | --- |
| id | string | The ID for user registered in the MIBcloud |
| email | string | User's email address registered in the MIBcloud |
| language | string | Default language code of user |
| account_ids | string list | The IDs associated with user |

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

| Parameter name | value | description |
| --- | --- | --- |
| product_id | string | Product ID to get gadgets |

Request body

* Do not supply a request body with this method.

Response

* Type: application/json

| key | value | description |
| --- | --- | --- |
| id | string | The generaged gadget ID |
| mac | string | MAC address of a gadget |
| name | string | Default name of a gadget |
| kind | string | Product ID of a gadget |
| firmware_version | string | Firmware version of a gadget |
| sdk_version | string | Compiled sdk version of a gadget |
| model_number | integer | Model number of a gadget |
| model_name | string | Model name of a gadget |
| hub_id | string | The IDs associated with a hub |
| account_id | string | The IDs associated with an account |
| user_id | string | The IDs associated with an user |
| status | integer | status code number of a gadget |
| rssi | integer | RSSI of a gadget with a hub |
| battery | integer | Battery level of a gadget |

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to call an endpoint |
| command | string | An endpoint commandP |

Request body

* Type: application/json

| key | value | description |
| --- | --- | --- |
| args | list | Arguments of endpoint |
| kwargs | dictionary | Key arguments of endpoint |
| key | string | Product key of a gadget product |
| otp | interger | (optional) Generated a otp number by salt |

Response

* Type: application/x-www-form-urlencoded

| value type | description |
| --- | --- |
| string | Task ID to get a result of an endpoint request |

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to get an result |
| tast_id | string | Task ID to get when it requested an endpoint |

Request body

* Do not supply a request body with this method.

Response

* Endpoint returned value

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to send a message |

Request body

* Type: application/json

| key | value | description |
| --- | --- | --- |
| title | string | Title of message |
| body | string | Messages |

Response

* True if requests is successed

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to send a message |

Request body

* Type: application/json

| key | value | description |
| --- | --- | --- |
| topic | string | Specified topic name of event |
| value | any | event value |

Response

* True if requests is successed

Example

* cURL

```http
$ curl -X POST "https://a.prota.space/v1/gadgets/{gadget_id}/event" -i -H "Authorization: Bearer {access_token}" -H "Content-Type: application/json" -d '{"topic": {topic}, "value": {value}}'
```

### Events
#### Overview

If register a hook url, product related all events are delivered to a hook url with POST method.

| type | value |
| --- | --- |
| method | POST |
| url | {registered hook url} |
| header | Authorization: Bearer {registered client key} |
| | Content-type: application/json |
| body | ```{"gadget_id": {gadget_id}, "topic": {event_topic}, "value": {event_value}``` |

#### Topics
* Paired a gadget to hub
| key | value |
| --- | --- |
| gadget_id | topic issuer |
| topic | gadget.paired |
| value | {GADGET DATA} |
* GADGET DATA
# MIBCloud 3rdparty Getting started

## Rest API reference
### Overview
URIs relative to https://a.prota.space/v1, unless otherwise noted

#### Authorization

Need to request with an access token. it is presented in https://console.microbot.is.

Example:

* curl
```http
$ curl '{REST_API_URL}' -i -H 'Authorization: Bearer {access_token}'
```

#### Request

Only supports a json format.

#### Response

Return value type is a json format.

### APIs
#### Users
##### **Gets a user's data by email.**
HTTP Request

```http
GET https://a.prota.space/v1/users/{email}
```

Parameters

* Path paramters

| Parameter name | value | description |
| --- | --- | --- |
| email | string | User's email address registered in the MIBcloud |

Request body

* Do not supply a request body with this method.

Response

* Type: application/json

| key | value | description |
| --- | --- | --- |
| id | string | The ID for user registered in the MIBcloud |
| email | string | User's email address registered in the MIBcloud |
| language | string | Default language code of user |
| account_ids | string list | The IDs associated with user |

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

| Parameter name | value | description |
| --- | --- | --- |
| product_id | string | Product ID to get gadgets |

Request body

* Do not supply a request body with this method.

Response

* Type: application/json

| key | value | description |
| --- | --- | --- |
| id | string | The generaged gadget ID |
| mac | string | MAC address of a gadget |
| name | string | Default name of a gadget |
| kind | string | Product ID of a gadget |
| firmware_version | string | Firmware version of a gadget |
| sdk_version | string | Compiled sdk version of a gadget |
| model_number | integer | Model number of a gadget |
| model_name | string | Model name of a gadget |
| hub_id | string | The IDs associated with a hub |
| account_id | string | The IDs associated with an account |
| user_id | string | The IDs associated with an user |
| status | integer | status code number of a gadget |
| rssi | integer | RSSI of a gadget with a hub |
| battery | integer | Battery level of a gadget |

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to call an endpoint |
| command | string | An endpoint commandP |

Request body

* Type: application/json

| key | value | description |
| --- | --- | --- |
| args | list | Arguments of endpoint |
| kwargs | dictionary | Key arguments of endpoint |
| key | string | Product key of a gadget product |
| otp | interger | (optional) Generated a otp number by salt |

Response

* Type: application/x-www-form-urlencoded

| value type | description |
| --- | --- |
| string | Task ID to get a result of an endpoint request |

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to get an result |
| tast_id | string | Task ID to get when it requested an endpoint |

Request body

* Do not supply a request body with this method.

Response

* Endpoint returned value

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to send a message |

Request body

* Type: application/json

| key | value | description |
| --- | --- | --- |
| title | string | Title of message |
| body | string | Messages |

Response

* True if requests is successed

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

| Parameter name | value | description |
| --- | --- | --- |
| gadget_id | string | Gadget ID to send a message |

Request body

* Type: application/json

| key | value | description |
| --- | --- | --- |
| topic | string | Specified topic name of event |
| value | any | event value |

Response

* True if requests is successed

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
| header | Authorization: Bearer {registered client key} |
| | Content-type: application/json |
| body | ```{"gadget_id": {gadget_id}, "topic": {event_topic}, "value": {event_value}``` |

##### Common Values
* GADGET DATA

| key | value | description |
| --- | --- | --- |
| id | string | The generaged gadget ID |
| mac | string | MAC address of a gadget |
| name | string | Default name of a gadget |
| kind | string | Product ID of a gadget |
| firmware_version | string | Firmware version of a gadget |
| sdk_version | string | Compiled sdk version of a gadget |
| model_number | integer | Model number of a gadget |
| model_name | string | Model name of a gadget |
| hub_id | string | The IDs associated with a hub |
| account_id | string | The IDs associated with an account |
| user_id | string | The IDs associated with an user |
| status | integer | status code number of a gadget |
| rssi | integer | RSSI of a gadget with a hub |
| battery | integer | Battery level of a gadget |


#### Common Topics
* Paired a gadget

| key | value |
| --- | --- |
| gadget_id | topic issuer |
| topic | gadget.paired |
| value | {GADGET DATA} |

* Connected a gadget with a hub

| key | value |
| --- | --- |
| gadget_id | topic issuer |
| topic | gadget.connected |
| value | {GADGET DATA} |

* Disonnected a gadget from a hub

| key | value |
| --- | --- |
| gadget_id | topic issuer |
| topic | gadget.disconnected |
| value | {GADGET DATA} |

* Unpaired a gadget

| key | value |
| --- | --- |
| gadget_id | topic issuer |
| topic | gadget.unpaired |
| value | {GADGET DATA} |
