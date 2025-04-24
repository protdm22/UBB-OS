#!/bin/bash

echo `git add .`
name=""
read -p "Enter commit name: " name
echo `git commit -m "$name"`
echo `git push -u origin main`

