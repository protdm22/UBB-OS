#!/bin/bash

ps -ef | grep -E -c "^$1"
