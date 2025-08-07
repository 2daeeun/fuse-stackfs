CC        = gcc
SRC_DIR   = src
OPS_DIR   = src/ops
SRCS      = $(wildcard $(SRC_DIR)/*.c $(OPS_DIR)/*.c)
OBJS      = $(SRCS:.c=.o)

# 링크 후 목적파일 삭제
.INTERMEDIATE: $(OBJS)

# pkg-config로 FUSE2 include/link 플래그 얻기
PKG_CFLAGS := $(shell pkg-config --cflags fuse)
PKG_LIBS   := $(shell pkg-config --libs fuse)

# 헤더 경로, FUSE_USE_VERSION 정의, 그리고 uftrace 계측 함수 훅 활성화
CFLAGS  = -Wall -Iinclude $(PKG_CFLAGS) -DFUSE_USE_VERSION=30 \
          -finstrument-functions -fno-omit-frame-pointer
LDFLAGS = $(PKG_LIBS) -lpthread

# 디버그 옵션 (make DEBUG=1)
ifeq ($(DEBUG),1)
  CFLAGS += -O0 -g
else
  # uftrace 상세 분석을 위해 기호는 항상 포함
  CFLAGS += -O2 -g
endif

# 실행 파일 이름
BIN = main

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OPS_DIR)/%.o: $(OPS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BIN)

