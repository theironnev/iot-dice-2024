/**
 * Manages 3D rendering and animation of a rotating cube using Three.js.
 *
 * Sets up the scene, camera, renderer, lights, and object loader.
 * Provides functions for rotating the cube to face a specific direction and continuous rotation.
 * Handles window resize events to adjust the renderer size.
 *
 * @link   https://yiidaatiihee30-iot-herkansers-ac4e5948a38373b988920532de73bdfe8.dev.hihva.nl/
 * @file   This file defines the 3D rendering and animation logic for a cube.
 * @author TheironneVelliam.
 * 
 */

import * as THREE from 'three'
import { GLTFLoader } from 'GLTFLoader';




let cube;
let rotationAxis = randomVector(); // Set a random rotation axis
let time = Date.now();
let isRotatingToFace = false;
let targetQuaternion = null;
let transitionDuration = 4000; // Duration in milliseconds to complete the transition
let transitionStartTime = 0;
let transitionElapsed = 0; // Elapsed time for transition
let enableRotation = false; // Flag to control continuous rotation
const rotationSpeed = 0.01; // Speed of rotation, radians per millisecond


//Canvas
const canvas = document.querySelector('canvas.webgl');

//Scene
var scene = new THREE.Scene();

//Camera
const sizes = { 
    width: window.innerWidth,
    hight: window.innerHeight
};
const camera = new THREE.PerspectiveCamera(45,sizes.width/sizes.hight) //Create camera object 
camera.position.z = 8;// MOve camera out of the way
scene.add(camera); // Add camera to scene

//Renderer 
const renderer = new THREE.WebGLRenderer({
    canvas:canvas //Give canvas to webgl canvas element
});
renderer.setSize(sizes.width, sizes.hight);

// Add some ambient light
var ambientLight = new THREE.AmbientLight(0xffffff, 0.9);
scene.add(ambientLight);

// directional light from bottom
var directionalLightBottom = new THREE.DirectionalLight(0x5b7df8, 2);//rgba(91, 125, 248, 0.781). button light
directionalLightBottom.position.set(0, -4, 1);
scene.add(directionalLightBottom);

// directional light from top
var directionalLightUp = new THREE.DirectionalLight(0xffffff, 2);
directionalLightUp.position.set(0, 4, 1);
scene.add(directionalLightUp);


//Object Loader
const loader = new GLTFLoader();
loader.load('../assets/Dice.glb',function(gltf){
                cube = gltf.scene;
                scene.add(cube);
                cube.position.set(0, 0, 0);

            }, function(xhr){
                // console.log((xhr.loaded / xhr.total * 100 ) + '% loaded');
            }, function(error){
                console.error(error);
            });



function randomVector() {
    const x = Math.random() * 2 - 1;
    const y = Math.random() * 2 - 1;
    const z = Math.random() * 2 - 1;
    const vector = new THREE.Vector3(x, y, z);
    vector.normalize();
    return vector;
}



const faceRotations = [
    new THREE.Quaternion().setFromEuler(new THREE.Euler(Math.PI / 2, 0, 0)), // face 1
    new THREE.Quaternion().setFromEuler(new THREE.Euler(0, Math.PI / 2, 0)), // face 2
    new THREE.Quaternion().setFromEuler(new THREE.Euler(0, 0, 0)),           // face 3
    new THREE.Quaternion().setFromEuler(new THREE.Euler(0, Math.PI, 0)),     // face 4
    new THREE.Quaternion().setFromEuler(new THREE.Euler(0, -Math.PI / 2, 0)), // face 5
    new THREE.Quaternion().setFromEuler(new THREE.Euler(-Math.PI / 2, 0, 0)) // face 6
    
];

export function rotateToFace(faceNumber) {
    if (faceNumber < 1 || faceNumber > 6) {
        console.error("Invalid face number. Choose a value between 1 and 6.");
        return;
    }
    targetQuaternion = faceRotations[faceNumber - 1];
    transitionStartTime = Date.now();
    transitionElapsed = 0;
    isRotatingToFace = true;
    enableRotation = false;  // Stop continuous rotation when rotating to a specific face
}

export function anim(){
    const currentTime = Date.now();
    const deltaT = currentTime - time;
    time = currentTime;

    if (cube) {
        if (isRotatingToFace) {
            transitionElapsed += deltaT;
            const fraction = transitionElapsed / transitionDuration;
            if (fraction < 1) {
                cube.quaternion.slerp(targetQuaternion, fraction);
            } else {
                cube.quaternion.copy(targetQuaternion);
                isRotatingToFace = false; // End rotation to face
            }
        } else if (enableRotation) {
            const rotationAmount = deltaT * rotationSpeed; // Calculate rotation based on deltaT
            cube.rotateOnAxis(rotationAxis, rotationAmount);
        }
    }

    renderer.render(scene, camera);
    window.requestAnimationFrame(anim);
};



// To start continuous rotation
export function startRotation() {
    enableRotation = true;
}


// Resize Event
window.addEventListener('resize', () => {
    sizes.width = window.innerWidth;
    sizes.height = window.innerHeight;
});