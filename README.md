# 🤖 bonkn't
### an arduino robot that absolutely refuses to bonk into things

![Arduino](https://img.shields.io/badge/Arduino-UNO-teal?style=flat-square&logo=arduino) ![Bonks](https://img.shields.io/badge/bonks-at%20least%201-red?style=flat-square)

> built so it wouldn't. and it doesn't. (mostly.)

---

## what even is this

an autonomous obstacle-avoiding robot that uses an ultrasonic sensor mounted on a servo to continuously scan its surroundings like a little radar. when something gets too close, it stops, looks left and right like it's crossing the street, reverses, and steers toward whichever side has more space.

no human input. no collisions. just vibes and physics.

---

## what's inside

| component | model | what it does |
|---|---|---|
| microcontroller | Arduino UNO (ATmega328P) | the brain |
| motor driver | L298N dual H-bridge | tells the wheels what to do |
| ultrasonic sensor | HC-SR04 (2–400 cm) | the eyes |
| servo motor | SG90 (0°–180°) | sweeps the sensor left and right |
| DC geared motors | with rubber wheels ×2 | the legs |
| battery pack | 4×AA (6V) | the heart (barely) |

---

## how it thinks

the servo sweeps back and forth between 20° and 160° the whole time the robot is moving, basically acting like a radar. distance is read at every 5° step.

**obstacle detected** (servo between 60°–120° AND distance < 20 cm):

```
stop → scan left & right → reverse → turn toward more space → go again
```

the left vs right decision is actually smart, it measures both sides and picks the one with more room rather than always turning the same direction. lil guy has opinions.

distance formula used:
```
distance (cm) = pulse duration (µs) ÷ 58.2
```

if no echo comes back within 20,000 µs → assumes clear path (returns 999 cm).

---

for full circuit details, pin config, and working principle — see [`docs/project_report.pdf`](docs/project_report.pdf)

---

## how to run this thing

1. wire everything up according to the pin table above (or check `docs/circuit_diagram.png`)
2. open `src/obstacle_avoiding_robot.ino` in Arduino IDE
3. plug in your Arduino UNO via USB
4. select the right board + port under **Tools**
5. hit upload
6. power the robot via the battery pack
7. put something in front of it and watch it refuse to bonk

open Serial Monitor at **9600 bps** to see real-time angle and distance readings while it runs, useful if you want to tune the 20 cm threshold.

---

## known quirks

- reflective or angled surfaces can scatter the ultrasonic beam and cause occasional false triggers
- the 450 ms turn duration is fixed, so it might over/under-rotate depending on surface friction or battery level
- only detects obstacles at sensor height, it will absolutely drive into a ramp or a very short wall
- one sensor means very narrow or multiple simultaneous obstacles can slip through

---


*at least 1 bonk recorded during testing. we do not talk about this.*
