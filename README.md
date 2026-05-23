# Shiritori

## Overview
The **Shiritori** is a specialized tool built for the AniList Anime Watching Club (AWC) Shiritori challenge:
https://anilist.co/forum/thread/73921/1

The Shiritori challenge requires you to watch 20 anime, where the last two letters of the previous anime match the first two letters of the following anime. The number of possible links between anime are hard to track and laborious to find. This tool automates the process of finding chains within eligible anime.

**Key Features:**
* **Automated Challenge Setup:** This tool prompts you to input your challenge post URL to extract username and challenge entry date. It then goes to request your anime list from AniList’s API.
* **Rule Enforcement:** Filters your anime list for eligible entries. According to the Shiritori challenge rules, the following conditions must be met:
- anime must have been started after posting the challenge entry comment
- minimum runtime per entry of 60 minutes or more
- format “Music” isn’t allowed
* **Chain Searching:** Evaluates all valid entries for all possible chains that met the conditions of the Shiritori challenge (English and Romaji titles are allowed, only the last anime in the chain can end on an ‘N’ and non-alphabetical characters are ignored and no 2-letter combinations can repeat).
* **Clean Export:** Outputs a ready-to-use `.tsv` (Tab-Separated Values) file sorted by chain length. Tab was chosen as the separator character, as anime titles may contain comman or semicolons. You can open .tsv file in excel or google sheets to receive the final list of all possible chains found in you anime list.

---

## Installation & Usage

This tool is entirely portable. There is no installer, and you do not need any programming knowledge to run it. It is only natively compatible with Windows systems.

### Step 1: Extract the Files
1. Download the Shiritori.zip file in the Deploy directory of this repository.
2. Extract the .zip file into a local directory of your choosing. Make sure the .exe file exists in the same directory as the .dll files, otherwise it won’t be able to communicate with AnilLst’s API.

### Step 2: Run the Tool
1. Inside the extracted folder, double-click `Shiritori.exe`.
2. A black console window will open.
3. When prompted, paste the full URL to your AniList challenge sign-up comment (e.g., `https://anilist.co/forum/thread/12345/comment/67890`) and press **Enter**.
4. The tool will download your list, process the chains, and notify you when it finishes. Press **Enter** to close the window.
5. Open the produced “chains.tsv” file in the directory it was run from to review the possible chains it found. You can directly open it with a local spreadsheet app like Excel or import it in Google Sheets.
### ⚠️ Note on Windows Defender (SmartScreen) and Smart App Control
Because this is a free, independently developed community tool without a commercial digital signature, Windows Defender will likely flag it with a **"Windows protected your PC"** warning. 

To run the tool:
1. Click **More info** on the blue popup.
2. Click the **Run anyway** button that appears at the bottom.

If you have activated Smart App Control, Windows may refuse to run this tool at all. In this case you would have to clone the repository locally and build it yourself, but even then Windows might block it.

If you are curious about how the tool works or want to verify its safety, the complete C++ source code is publicly available in this repository. You may also check the file with VirusTotal or similar tools that scan applications for malicious behaviour.
