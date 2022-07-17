# esp32-ir

## Usage

* platformio
  * IRremoteESP8266
  * Arduino_JSON

### Compile

```sh
$ cat << EOF > src/secret.h
    const char* SSID = "<ssid>";
    const char* WIFI_PASSWORD = "<password>";
EOF
  
$ pio run
```

### Upload

```sh
$ pio run -t upload
```

### Upload (via ota)

```sh
$ pio run -t upload --upload-port '<ip-address>'
```
