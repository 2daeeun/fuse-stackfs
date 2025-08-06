#!/bin/bash

# 1) compile_commands.json 생성 함수
GENERATE_COMPILE_COMMANDS() {

  # 스크립트 실행 중 오류 발생 시 중단
  set -e

  # bear 실행
  echo -e "\nncompile_commands.json을 생성합니다...\n"
  bear -- make
  echo -e "\n작업이 완료되었습니다!"
}

# 2) compile 함수
COMPILE() {

  # compile_commands.json 파일 확인
  if [ ! -f "compile_commands.json" ]; then
    echo "compile_commands.json 파일이 없습니다. 생성합니다..."
    GENERATE_COMPILE_COMMANDS
  else
    echo "compile_commands.json 파일이 이미 존재합니다."
  fi

  # make 실행
  echo -e "\nmake 실행 중...\n"
  make clean && make
  echo -e "\n작업이 완료되었습니다!"
}

# 3) mount 함수
MOUNT() {

  # 마운트 실행
  echo -e "\n마운트를 실행합니다."
  echo -e "\n마운트 명령어:\n"
  echo -e "sudo ./sfuse /dev/nvme0n1p6 /mnt/partition_06_4GB -f -s -d -o allow_other"
  echo -e "\n"
  sudo ./StackFS_ll -r temp_mount -f -d /mnt/partition_06_4GB

  # 언마운트
  # sudo fusermount3 -u /tmp/sfuse
  # sudo umount /mnt/partition_04_200MB
  # sudo dd if=/dev/zero of=/dev/nvme0n1p4 bs=4M status=progress && sync
  # sudo mkfs.ext2 /dev/nvme0n1p4
  # sudo mount /dev/nvme0n1p4 /mnt/partition_04_200MB
}

# 옵션 출력
echo -e "┌───────────────옵션───────────────┐"
echo -e "│ 1) compile_commands.json 생성    │"
echo -e "│ 2) 컴파일                        │"
echo -e "│ 3) 파일 기반 블록 디바이스 마운트│"
echo -e "│ q) 종료                          │"
echo -e "└──────────────────────────────────┘"

# 사용자 입력 받기
read -p "선택: " choice

case $choice in
1)
  # compile_commands.json 생성 함수 실행
  GENERATE_COMPILE_COMMANDS
  ;;
2)

  # compile 함수 실행
  COMPILE
  ;;
3)
  # MOUNT 함수 실행
  MOUNT
  ;;
q)
  echo "종료합니다."
  exit 0
  ;;
*)
  echo "잘못된 입력입니다. 스크립트를 다시 실행해주세요."
  exit 1
  ;;
esac
