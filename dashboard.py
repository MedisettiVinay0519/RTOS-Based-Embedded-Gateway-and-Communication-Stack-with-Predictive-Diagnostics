import pandas as pd
import matplotlib.pyplot as plt

# ---------------------------
# Load feature dataset
# ---------------------------
df = pd.read_csv("feature_dataset.csv")

time = range(1, len(df)+1)

# ===========================
# Gateway Health Trend
# ===========================
plt.figure(figsize=(8,5))
plt.plot(time, df["gateway_health"])
plt.xlabel("Sample")
plt.ylabel("Health (%)")
plt.title("Gateway Health Trend")
plt.grid()
plt.savefig("health_trend.png")
plt.show()


# ===========================
# CRC Errors
# ===========================
plt.figure(figsize=(8,5))
plt.plot(time, df["crc_errors"])
plt.xlabel("Sample")
plt.ylabel("CRC Errors")
plt.title("CRC Error Trend")
plt.grid()
plt.savefig("crc_trend.png")
plt.show()


# ===========================
# Packet Loss
# ===========================
plt.figure(figsize=(8,5))
plt.plot(time, df["packet_loss"])
plt.xlabel("Sample")
plt.ylabel("Packet Loss")
plt.title("Packet Loss Trend")
plt.grid()
plt.savefig("packet_loss_trend.png")
plt.show()


# ===========================
# Device Errors
# ===========================
plt.figure(figsize=(8,5))
plt.plot(time, df["device_errors"])
plt.xlabel("Sample")
plt.ylabel("Device Errors")
plt.title("Device Error Trend")
plt.grid()
plt.savefig("device_error_trend.png")
plt.show()


# ===========================
# Isolation Forest Score
# ===========================
plt.figure(figsize=(8,5))
plt.plot(time, df["score"])
plt.axhline(y=0,color='r')
plt.xlabel("Sample")
plt.ylabel("IF Score")
plt.title("Isolation Forest Score")
plt.grid()
plt.savefig("iforest_score.png")
plt.show()


# ===========================
# Anomaly Timeline
# ===========================
plt.figure(figsize=(8,5))

colors=[]

for p in df["prediction"]:
    if p==-1:
        colors.append('red')
    else:
        colors.append('blue')

plt.scatter(time,
            df["gateway_health"],
            c=colors)

plt.xlabel("Sample")
plt.ylabel("Gateway Health")
plt.title("Anomaly Timeline")
plt.grid()

plt.savefig("anomaly_timeline.png")
plt.show()