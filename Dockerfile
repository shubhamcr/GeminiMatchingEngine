FROM debian:10
RUN apt-get -y update \
  && apt-get -y install build-essential \
  && apt-get clean
COPY src/ /app/src
COPY googletest/ /app
RUN cd /app/src && make build && make test
