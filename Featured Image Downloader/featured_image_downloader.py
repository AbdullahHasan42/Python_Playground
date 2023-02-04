import requests
import os
from bs4 import BeautifulSoup


def download_image():
    # Gets the web page as plain text
    url = "https://wall.alphacoders.com/"
    source_code = requests.get(url)
    plain_text = source_code.text
    soup = BeautifulSoup(plain_text, 'html.parser')

    # Locates the link of the featured image
    # gets the image format , ID number, uploader name and removes the thumbnail resolution
    source_link = soup.find("img", {"class": "img-responsive", "alt": True})['src']
    uploader_name = soup.find("div", {"class": "featured-categorization"})
    uploader_name = uploader_name.find_all("a")[2].text.strip()
    uploader_name = uploader_name.split(": ")[1]
    image_format = source_link[-4:]
    image_id = source_link[-10:-4]
    featured_image_link = source_link.replace("thumb-350-", "")

    # Gets the image as a response object
    full_sized_image = requests.get(featured_image_link)

    # Locates and stores the parent dir for the script
    p_dir = os.path.dirname(__file__)

    # Save the image response to an image file
    with open(p_dir +"\\"+ image_id + "_" + uploader_name + image_format, 'wb') as f:
        f.write(full_sized_image.content)


download_image()
