FROM treefrogframework/treefrog

RUN apt update
RUN apt install -y git

COPY . /app

WORKDIR /app

RUN qmake -r "CONFIG+=release"
RUN mkdir build
RUN cd build && cmake ../
RUN cd build && make

CMD treefrog -e dev
