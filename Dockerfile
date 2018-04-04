FROM bluebell/debian-ola
COPY . ./workdir
WORKDIR ./workdir
RUN make
CMD ./talking-dockers $MODE
