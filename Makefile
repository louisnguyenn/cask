IMAGE_NAME=cask-dev
CONTAINER_NAME=cask-container

docker-build:
	docker build -f .devcontainer/Dockerfile -t $(IMAGE_NAME) .

docker-run:
	docker run -it --name $(CONTAINER_NAME) -v $(PWD):/app $(IMAGE_NAME)

docker-clean:
	docker rm -f $(CONTAINER_NAME) || true
	docker rmi $(IMAGE_NAME) || true
