# !pip install pyarabic

from bs4 import BeautifulSoup
from requests import get
import pandas as pd
import numpy as np
from tqdm import tqdm
from pyarabic.araby import tokenize, normalize_hamza, is_arabicrange
import ast


# Gets the web page table
# Loop over the needed pages
def get_movies_names_and_links(pgNum):
    
    movie_list = []
    
    for i in tqdm(range(6,pgNum+6)):
        url = "https://elcinema.com/index/work/country/eg?page=" + str(i+1)
        source_code = get(url)
        plain_text = source_code.text
        table_soup = BeautifulSoup(plain_text, 'html.parser')

        html_table = table_soup.find("table", attrs={"class":"expand"})
        movie_table = html_table.find_all('a', text=True)        

        for movie in movie_table:
                movie_list.append({"movie_ID": movie['href'][-8:-1], "Name": movie.text, "Link": "https://elcinema.com" + movie['href']})
        

    movie_name_link = pd.DataFrame(movie_list)
    
    return movie_name_link


def get_genre_and_plot(movie_link):
    movie_page_src = get(movie_link)
    movie_page_text = movie_page_src.text
    movie_page_soup = BeautifulSoup(movie_page_text, 'html.parser')
    
    genre_id = []
    plot_sum = []
    
    try:
        status = movie_page_soup.find(['ul'], {"class": "list-separator"})
        status = status.find_all('li')[3].text  # To get the aired status
    except AttributeError:
        genre_id.append('None')
        plot_sum.append('None')
    
    if status == 'ﺗﻢ ﻋﺮﺿﻪ':
        try:       
            genre_labels = movie_page_soup.find('ul', attrs={"id": "jump-here-genre"})
            genre_labels = genre_labels.find_all('a')
            
            for label in genre_labels:
                genre_id.append(label.text)
            
            plot_summary = movie_page_soup.find(['p'])
            plot_summary = plot_summary.text.replace("..اقرأ المزيد", "")
            plot_sum.append(plot_summary)
        
        except AttributeError:
            genre_id.append('None')
            plot_sum.append('None')
    else:
        genre_id.append('None')
        plot_sum.append('None')

    return genre_id, plot_sum, movie_link


# movie_name_link = get_movies_names_and_links(500)
genre_and_plot = []
target = movie_name_link[3878:]


for i in tqdm(range(0,len(target))):
    movie_link = target['Link'][i]
    genre_and_plot.append(get_genre_and_plot(movie_link))


genre_and_plot_data = pd.DataFrame(genre_and_plot, columns=['Genre', 'Plot', "VERIFY LINK"])
movie_data = pd.concat([movie_name_link, genre_and_plot_data], axis=1)


for i in tqdm(range(0, len(movie_data))):
    try:
        movie_data['Plot'][int(i)] = "".join(movie_data['Plot'][int(i)])
        
    except TypeError:
        pass


data = pd.read_excel("movies_data.xlsx")
data = data.dropna()
data = data.reset_index()


tokenized_plot = []

for i in tqdm(range(0,len(data['Plot']))):
    sentence = normalize_hamza(data['Plot'][i])
    tokenized_plot.append(','.join(tokenize(sentence, conditions=is_arabicrange)))


data['Tokenized Plot'] = tokenized_plot


cleaned = []

for i in tqdm(range(0,len(data['Genre']))):
    data.iloc[i,4] = ', '.join(ast.literal_eval(data.iloc[i,4]))
