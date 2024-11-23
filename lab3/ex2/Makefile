CPP = g++ # Flag for implicit rule
CC = gcc # Flag for implicit rule
LD = ld # Flag for implicit rule
AR = ar
GFLAGS = -std=c++11 -g -pthread -I./ -L. # Bỏ -fPIE để không yêu cầu mã độc lập vị trí
CFLAGS = -g -pthread -I./ -L. # Không cần -fPIC vì không thể biên dịch lại libutils.a
LFLAGS = -g -pthread -no-pie # Thêm -no-pie vào cờ liên kết
ARFLAGS = rcs

COBJECT = main 
CEXEC = aggsum
LIBS = utils

COBJECTO = $(addsuffix .o,$(COBJECT))
CLIBS = $(addprefix lib,$(addsuffix .a,$(LIBS)))

%.o: %.cpp
	$(CPP) $(GFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

lib%.a: %.o
	$(AR) $(ARFLAGS) $@ $^

all: $(COBJECTO) $(CLIBS)
	$(CC) $(LFLAGS) -o $(CEXEC) $(COBJECTO) -L. -l$(LIBS) # Đảm bảo -no-pie được áp dụng tại đây

clean:
	rm -f *.o
	rm -f $(CEXEC)
	rm -f $(CLIBS)
