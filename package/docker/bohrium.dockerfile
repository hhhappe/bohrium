# This is a Dockerfile for installing and testing Bohrium
# It is based on the image 'bohrium/ubuntu', which must be on docker hub or locally.
# Please make sure that the build "context" is pointing to the root of Bohrium source files
# e.g. 'docker build -t bohrium -f <path to this file> <path to bohrium source>'
# Then you can run 'docker run -t bohrium' to Bohrium test

FROM bohrium/ubuntu:16.04
MAINTAINER Mads R. B. Kristensen <madsbk@gmail.com>

# Set the locale
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

# Download benchpress
RUN mkdir -p /benchpress
WORKDIR /benchpress/
RUN wget -nv https://github.com/bh107/benchpress/archive/master.zip
RUN unzip -q master.zip
ENV PATH "/benchpress/benchpress-master/bin:$PATH"
ENV PYTHONPATH "/benchpress/benchpress-master/module:$PYTHONPATH"

# Copy and build bohrium source files from "context"
RUN mkdir -p /bohrium/build
WORKDIR /bohrium/build
COPY . ../
RUN cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr -DEXT_VISUALIZER=OFF -DUSE_WERROR=ON
RUN make
RUN make install

# Test Suite
WORKDIR /bohrium
ENTRYPOINT export PYTHONPATH="/usr/lib/$PYTHON_EXEC/site-packages:$PYTHONPATH" && export && /usr/bin/bh-info && $PYTHON_EXEC /bohrium/test/python/run.py /bohrium/test/python/tests/test_*.py && $PYTHON_EXEC /bohrium/test/python/numpytest.py --file test_benchmarks.py
