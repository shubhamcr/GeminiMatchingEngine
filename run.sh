#!/bin/bash
sudo docker build -t gemini_interview . && docker run -i --rm gemini_interview /app/src/build/match_engine