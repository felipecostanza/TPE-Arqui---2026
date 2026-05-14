docker start DockerPrueba2
echo 'hola'
docker exec -it DockerPrueba2 make clean -C /root/Toolchain
echo 'hol2a'


docker exec -it DockerPrueba2 make clean -C /root/
docker exec -it DockerPrueba2 make -C /root/Toolchain
docker exec -it DockerPrueba2 make -C /root/