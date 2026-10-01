# Robotics SWE Roadmap — From Pub/Sub to Nav2

**Starting point confirmed:** You know ROS2 Topics, Publishers, Subscribers, Services, Clients, Servers. Everything below assumes that foundation and builds forward.

**Stack recommendation:** Use **ROS2 Jazzy + Gazebo Harmonic**. This is the current standard pairing being taught and used in 2026 — Jazzy is LTS until 2029, and Nav2/TurtleBot3 tutorials are actively maintained on it. If your existing `robotics` repo is already on Humble, don't migrate — Humble is still supported until 2027 and the *concepts* transfer 1:1. Only the install commands differ.

---

## Legend

- **Difficulty:** 🟢 Beginner · 🟡 Intermediate · 🔴 Advanced
- **Time:** hours to reach *practical competency* — meaning you can use it, configure it, and debug it. Not deep mathematical mastery.
- **Tag:** `MUST-KNOW` (non-negotiable for any robotics SWE intern application) or `GREAT-TO-KNOW` (differentiator, do only after must-knows are solid)

---

## Reality Check (read this before you start)

> **Be honest with yourself about the timeline.** "Learn ROS2 in 30 days" content on YouTube/Udemy teaches copy-paste execution, not debugging skill — and debugging skill is exactly what gets tested in interviews and take-home assignments. This roadmap is written for genuine competency, not a certificate.

> **This is a 5-8 month project at 1-2 hours a day, not a few weeks.** Total core work is roughly 195-200 hours. At 1.5 hrs/day (≈10.5 hrs/week) that's about 19 weeks (~4.5 months) for the must-know core alone, plus projects. If some days you only get 45 minutes — that's fine, it pushes the date, it doesn't break the plan.

> **Depth over breadth, always.** One project that's fully working, documented, and demoed with a video/GIF beats five half-finished ones. Recruiters at places like Black Coffee Robotics and Acceleration Robotics skim GitHub in under a minute — a broken repo with 10 abandoned experiments reads worse than 2 finished ones.

> **Hardware is a real bottleneck, not an afterthought.** The single highest-differentiator project below needs an actual ESP32/Arduino (~₹800-1500) and basic sensors. Order it now, not when you get to that phase — shipping and customs delays in India are real.

> **Don't chase every "great-to-know" item.** Isaac Sim is genuinely GPU-heavy — if your machine can't run it well, skip it and say so honestly in interviews rather than burning 10 hours fighting driver issues. Prioritize great-to-know items that specific target companies actually mention (Isaac Sim is explicitly listed in Black Coffee Robotics postings — Cartographer generally isn't).

> **GATE 2027 note:** since this is your trial attempt (not the one that counts), don't fully pause robotics work for it. Save the hard pause for GATE 2028 prep.

---

## Phase 1 — The Rest of ROS2 Core `MUST-KNOW`

- [ ] **Actions** (goal/feedback/result pattern) — 🟡 Intermediate, ~5-6h
  Nav2 itself is built entirely on actions. You cannot understand navigation without this.
- [ ] **Parameters + YAML config** — 🟢 Beginner, ~3-4h
  Every real ROS2 node is configured through parameters, not hardcoded values.
- [ ] **Launch files (Python launch system)** — 🟢 Beginner-Intermediate, ~5h
  How you start multi-node systems. Non-negotiable for any real project.
- [ ] **Custom interfaces** (custom `.msg`/`.srv`/`.action` definitions) — 🟢 Beginner, ~4h
- [ ] **TF2** (transform trees, broadcasters, listeners, static vs dynamic transforms) — 🟡 Intermediate, ~7-8h
  This is the concept most beginners underestimate and most interviews probe. Don't rush it.
- [ ] **QoS profiles** (reliability, durability, history depth) — 🟡 Intermediate, ~3h
- [ ] **`ros2 bag` record/playback** — 🟢 Beginner, ~2h
- [ ] **Debugging toolkit**: `rqt_graph`, `ros2 doctor`, `ros2 topic hz/bw`, logging levels — 🟢 Beginner, ~3h
- [ ] **colcon workspace structure & package.xml/CMakeLists best practices** — 🟢 Beginner, ~3h

**Phase 1 subtotal: ~32-37h**

- [ ] *(GREAT-TO-KNOW)* **Lifecycle nodes & component composition** — 🔴 Advanced, ~5h — matters more for production-grade/managed systems, less for internships.

---

## Phase 2 — Robot Description `MUST-KNOW`

- [ ] **URDF fundamentals** (links, joints, visual/collision/inertial tags) — 🟡 Intermediate, ~6h
- [ ] **Xacro** (macros, parameterized robot descriptions) — 🟡 Intermediate, ~4h
- [ ] **`robot_state_publisher` + `joint_state_publisher`** — 🟢 Beginner, ~3h
- [ ] **Visualizing in RViz2** (TF frames, markers, robot model display) — 🟢 Beginner, ~3h

**Phase 2 subtotal: ~14-16h**

---

## Phase 3 — Simulation `MUST-KNOW`

- [ ] **Gazebo Harmonic basics** (worlds, SDF, physics engine settings) — 🟡 Intermediate, ~6h
- [ ] **Spawning a robot + plugins** (diff-drive plugin, joint control plugin) — 🟡 Intermediate, ~6h
- [ ] **Simulating sensors** (camera, LiDAR, IMU — noise models included) — 🟡 Intermediate, ~5h
- [ ] **`ros2_control` + hardware interface abstraction** — 🔴 Advanced, ~8h
  This is what lets the *same* control code run in simulation and on real hardware later — genuinely important, don't skip it.

**Phase 3 subtotal: ~25h**

- [ ] *(GREAT-TO-KNOW)* **NVIDIA Isaac Sim intro** — 🔴 Advanced, ~10h — high recruiter signal (explicitly in Black Coffee Robotics postings) but GPU-heavy. Check your machine first.

### 🔧 Project checkpoint: Build #2 (see Projects section)

---

## Phase 4 — Perception Basics `MUST-KNOW (light)` + `GREAT-TO-KNOW (deeper)`

- [ ] **`cv_bridge` + OpenCV in ROS2** — 🟡 Intermediate, ~5h
- [ ] **Camera calibration** — 🟡 Intermediate, ~3h
- [ ] **ArUco/AprilTag marker detection** — 🟡 Intermediate, ~4h

**Phase 4 subtotal: ~12h**

- [ ] *(GREAT-TO-KNOW)* **Point cloud basics (PCL)** — 🔴 Advanced, ~6h — worth it if targeting perception-heavy roles specifically.

---

## Phase 5 — Localization & SLAM `MUST-KNOW`

- [ ] **Odometry & coordinate frame recap** (`odom` → `base_link`, drift) — 🟡 Intermediate, ~3h
- [ ] **`robot_localization` (EKF sensor fusion)** — 🔴 Advanced, ~6-7h
  Fusing wheel odometry + IMU. Genuinely one of the best "I understand real robotics, not just tutorials" signals you can show.
- [ ] **Occupancy grid mapping — concepts** — 🟡 Intermediate, ~4h
- [ ] **`slam_toolbox` (practical usage)** — 🟡 Intermediate, ~6h
- [ ] **AMCL / particle filter localization — concept + practical tuning** — 🔴 Advanced, ~5h

**Phase 5 subtotal: ~24-25h**

- [ ] *(GREAT-TO-KNOW)* **Cartographer overview** — 🔴 Advanced, ~3h
- [ ] *(GREAT-TO-KNOW)* **Visual SLAM overview (ORB-SLAM, conceptual)** — 🔴 Advanced, ~3h

### 🔧 Project checkpoint: Build #3

---

## Phase 6 — Navigation: Nav2 `MUST-KNOW`

- [ ] **Nav2 architecture overview** (lifecycle managers, servers) — 🟡 Intermediate, ~3h
- [ ] **Costmaps** (global/local, layers, inflation, obstacle layer) — 🟡 Intermediate, ~5h
- [ ] **Planners** (NavFn, Smac Planner) — 🟡 Intermediate, ~4h
- [ ] **Controllers** (DWB, Regulated Pure Pursuit) — 🟡 Intermediate, ~4h
- [ ] **Behavior Trees in Nav2** — 🔴 Advanced, ~6h
  This is where most beginners plateau. Push through it — it's what makes Nav2 "programmable" instead of a black box.
- [ ] **Recovery behaviors + waypoint following** — 🟡 Intermediate, ~3h
- [ ] **Parameter tuning (practical, on your own robot)** — 🔴 Advanced, ~5h

**Phase 6 subtotal: ~30h**

### 🔧 Project checkpoint: Build #1 (your flagship project) + Build #4

---

## Phase 7 — Manipulation `GREAT-TO-KNOW` (optional, do only if time allows)

- [ ] **Forward/Inverse kinematics basics** — 🔴 Advanced, ~5h
- [ ] **MoveIt2 intro** — 🔴 Advanced, ~8h
- [ ] **Grasping basics** — 🔴 Advanced, ~4h

**Subtotal (skip unless targeting arm/manipulation-specific roles): ~17h**

---

## Phase 8 — Hardware Bridge `MUST-KNOW (minimal)` + `GREAT-TO-KNOW (full)`

- [ ] **Serial/UART bridge node** (Python or C++ node talking to Arduino/ESP32 over UART) — 🟡 Intermediate, ~5-6h
  This is where your UART interest from before pays off directly.

**Subtotal: ~6h**

- [ ] *(GREAT-TO-KNOW)* **micro-ROS on ESP32** (native ROS2 nodes on the microcontroller itself) — 🔴 Advanced, ~8h — this is the single biggest differentiator on this entire list. Almost no student portfolios have this.

### 🔧 Project checkpoint: Build #5

---

## Phase 9 — Systems & 2026 Differentiators `GREAT-TO-KNOW`

- [ ] **Docker for ROS2** (reproducible dev environments) — 🟡 Intermediate, ~5h
- [ ] **Basic CI** (`colcon test` + GitHub Actions) — 🔴 Advanced, ~4h
- [ ] **Isaac ROS overview** — 🔴 Advanced, ~10h (only if Phase 3's Isaac Sim went well)
- [ ] **LLM → ROS2 action parsing** (small project: parse natural-language commands into Nav2 goals) — 🔴 Advanced, ~8-10h
  Genuinely trending — current job listings specifically ask whether candidates can bridge LLMs into ROS action calls. High recruiter novelty for relatively low build time.

---

## Projects — Ranked by Recruiter Impact

Build these in roughly this order, interleaved with the phases above (each is tagged with when you can realistically start it).

### Build #1 — Autonomous Navigation Stack (your flagship) — ~20h
*Start after Phase 5 + 6.* Differential-drive robot in Gazebo, mapped with `slam_toolbox`, navigating autonomously via Nav2, visualized in RViz2. **This is the one every recruiter expects to see.** Without it, you don't clear the initial screen at either target company. Document it with a GIF of the robot navigating and a short README explaining your costmap/planner choices.

### Build #2 — Original Robot from Scratch — ~10h
*Start after Phase 3.* Design your own URDF (not a TurtleBot3 clone), get it into Gazebo with `ros2_control`, add teleoperation. Signals you can build, not just run tutorials.

### Build #3 — Sensor Fusion Localization — ~8h
*Start after Phase 5.* Fuse wheel odometry + IMU with `robot_localization`. Plot raw odometry drift vs. fused estimate side-by-side — a visual proof of improvement is a strong, easy-to-skim portfolio signal.

### Build #4 — Perception-Triggered Navigation — ~8h
*Start after Phase 4 + 6.* Detect an ArUco tag, use it to trigger a Nav2 waypoint goal. Bridges perception and navigation — genuinely rare in student portfolios, most people only do one or the other.

### Build #5 — Real Hardware Bridge — ~12h
*Start after Phase 8.* A UART/micro-ROS node driving actual motors/sensors on real hardware, not just simulation. **This is your biggest single differentiator** — both Black Coffee Robotics and Acceleration Robotics explicitly mention "driver development" and "hardware acceleration" in their listings. Proves you're not simulation-only.

### Build #6 (stretch) — Natural Language Robot Commands — ~8-10h
*Only if everything above is solid and documented.* Small app where a text command gets parsed by an LLM API call into a Nav2 goal pose. High novelty, on-trend for 2026.

> **Honest note on projects:** if you only finish Builds #1, #2, and #5 — fully working, well-documented, with demo videos — that alone would put you ahead of most applicants at your level. Don't feel obligated to hit all six.

---

## Timeline — Your Actual Deadline

Total estimated hours:

| Scope | Hours |
|---|---|
| Must-know concepts (Phases 1,2,3,4-light,5,6,8-light) | ~145h |
| Core projects (Builds #1-#5) | ~58h |
| **Core total** | **~200h** |
| Great-to-know additions (Phases 7, 9, Build #6) | ~90h |
| **Everything, including differentiators** | **~290h** |

### Pace sensitivity — starting today, July 28, 2026

| Daily pace | Core roadmap done by | Everything done by |
|---|---|---|
| 1 hr/day (worst case) | ~early February 2027 | ~mid-April 2027 |
| 1.5 hr/day (realistic target) | ~mid-December 2026 | ~late January 2027 |
| 2 hr/day (best case) | ~early November 2026 | ~mid-December 2026 |

**Your working deadline: treat mid-December 2026 as the checkpoint for the must-know core + Builds #1, #2, #3.** That's realistic at 1.5 hrs/day. If you're only managing 1 hr some days — which will happen — early February 2027 is still a completely respectable, honest fallback and still leaves you well ahead of a 3rd-year internship application cycle.

Push Build #5 (hardware) and any great-to-know items into January-February 2027, after ordering your ESP32/sensors now so they're not a bottleneck later.
