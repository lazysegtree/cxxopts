import argparse

def main():
    parser = argparse.ArgumentParser(
        prog="git",
        description="Simulated git command"
    )

    subparsers = parser.add_subparsers(
        title="subcommands",
        dest="command",
        required=True
    )

    # ---- git pull ----
    pull_parser = subparsers.add_parser(
        "pull",
        help="Fetch from and integrate with another repository or a local branch"
    )
    # ---- git commit ----
    commit_parser = subparsers.add_parser(
        "commit",
        help="Record changes to the repository",
        description="Record changes to the repository"
    )

    commit_parser.add_argument("-m",help="Message", type=str)
    args = parser.parse_args()
    print(f"args are {args}")

if __name__ == "__main__":
    main()
