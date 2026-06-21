import pandas as pd
from sklearn.ensemble import IsolationForest

# Read logs
packet_df = pd.read_csv("packet_log.csv")
gateway_df = pd.read_csv("gateway_log.csv")

# Cumulative counts
crc_errors = (
    gateway_df["Message"]
    .str.contains("CRC Error")
    .cumsum()
)

device_errors = (
    gateway_df["Message"]
    .str.contains("Device Error")
    .cumsum()
)

packet_drops = (
    gateway_df["Message"]
    .str.contains("Packet Dropped")
    .cumsum()
)

# Feature dataframe
features = pd.DataFrame()

features["crc_errors"] = crc_errors
features["device_errors"] = device_errors
features["packet_loss"] = packet_drops

features["packets"] = range(
    1,
    len(features) + 1
)

features["success_rate"] = (
    (
        features["packets"]
        - features["packet_loss"]
    )
    /
    features["packets"]
) * 100

features["gateway_health"] = (
    100
    - features["packet_loss"]
    - features["crc_errors"]
    - features["device_errors"]
)

# Only these columns are used for training
X = features[
    [
        "crc_errors",
        "device_errors",
        "packet_loss",
        "packets",
        "success_rate",
        "gateway_health"
    ]
]

# Train Isolation Forest
model = IsolationForest(
    contamination=0.1,
    random_state=42
)

model.fit(X)

# Predictions
features["score"] = model.decision_function(X)

features["prediction"] = model.predict(X)

print(features.tail())

print(
    "\nMinimum score =",
    features["score"].min()
)

features.to_csv(
    "feature_dataset.csv",
    index=False
)