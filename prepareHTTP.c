

typedef struct {
    char *verb;
    char *resource;
    char *domain;
    char *resourceData;
    char *postData;
    int port;
} http_request_options;

/**
 * Build HTTP Request
 *
 * \param struct 	http_request_options
 *
 * \return integer	Error Code
 */
int buildRequest(http_request_options *options, char *sendBuffer) {
  char *verb = options->verb;
  char *resource = options->resource;
  char *domain = options->domain;
  char *resourceData = options->resourceData;
  char *postData = options->postData;

	char contentLength[5] = "";
  strcpy(sendBuffer, verb);
  strcat(sendBuffer, " ");
  strcat(sendBuffer, resource);
  if (strcmp(verb, "GET") == 0) {
  	if (resourceData && resourceData[0] != '\0' ) {
  		strcat(sendBuffer, resourceData);
  	}
  }
  strcat(sendBuffer, " HTTP/1.1");
  strcat(sendBuffer, "\r\n");
  strcat(sendBuffer, "User-Agent: Filezilla\r\n");
  strcat(sendBuffer, "Host: ");
  strcat(sendBuffer, domain);
  strcat(sendBuffer, "\r\n");
	strcat(sendBuffer, "Accept: */*\r\n");

  if (strcmp(verb, "GET") == 0) {
  	strcat(sendBuffer, "\r\n");
  } else if (strcmp(verb, "POST") == 0) {
  	// strcat(sendBuffer, "Content-Type: application/x-www-form-urlencoded\r\n");
		// strcat(sendBuffer, "Content-Type: application/json\r\n");
		// strcat(sendBuffer, "x-accept-version: 2.0.0\r\n");
		strcat(sendBuffer, "Content-Length: ");
		sprintf(contentLength, "%lu", strlen(postData));
		strcat(sendBuffer, contentLength);
		strcat(sendBuffer, "\r\n\r\n"); //Two return lines after headers
		strcat(sendBuffer, postData);
  } else {
  	printf("unused verb:%s", verb);
  	return -1;
  }

  return 0;
}

