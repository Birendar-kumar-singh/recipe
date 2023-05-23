#include <bits/stdc++.h>
using namespace std;
vector<string> possible_recipes;
unordered_map<string, vector<string>> recipes {
    {"egg curry", {"egg", "tomato", "onion", "garlic", "oliveoil"}},
    {"fired rice", {"rice", "soy sauce", "garlic", "ginger", "vegetables", "oil"}},
    {"chicken curry", {"chicken", "tomato", "ginger", "onion", "potatoes", "garlic"}},
    {"dosa",{"dosabatter","onion","oliveoil"}},
    {"dosabatter",{"uraddal","rice"}}
};

bool check_items(string recipe){
    for(auto d:recipes){
            for(auto e:d.second){
                if(e == recipe){
                   return true; 
                }
            }
        }
        return false;
}
vector<string> remove_items(string recipe,vector<string> &ingredients){
    for(auto item:recipes[recipe]){
        if(find(ingredients.begin(),ingredients.end(),item) != ingredients.end()){
        auto i=find(ingredients.begin(),ingredients.end(),item);
        ingredients.erase(i);
            
        } else {
            ingredients.clear();
        }
    }
    return ingredients;
}
vector<string> find_recipes(vector<string>& ingredients) {
    for (auto const& [recipe, recipe_ingredients] : recipes) {
        if (all_of(recipe_ingredients.begin(), recipe_ingredients.end(),
            [&ingredients](const string& ingredient) {
                return find(ingredients.begin(), ingredients.end(), ingredient) != ingredients.end();
            })) {
            possible_recipes.push_back(recipe);
        }
        if(ingredients.empty()){
            return possible_recipes;
        }
    }
    if(possible_recipes.empty()){
        return possible_recipes;
    }else{
    bool c = check_items(possible_recipes.back());
    if(c){
        ingredients.push_back(possible_recipes.back());
        ingredients = remove_items(possible_recipes.back(),ingredients);
        possible_recipes = find_recipes(ingredients);
    }
    }
    return possible_recipes;
}
void remove_space(string &str){
    int l =str.length();
    int c = count(str.begin(),str.end(),' ');
    remove(str.begin(),str.end(),' ');
    str.resize(l-c);
}

int main() {
    string input;
    cout << "Enter the ingredients that you have in your kitchen, separated by commas: ";
    getline(cin, input);
    remove_space(input);
    vector<string> input_ingredients;
    string ingredient;
    istringstream ss(input);
    while (getline(ss, ingredient, ',')) {
        transform(ingredient.begin(), ingredient.end(), ingredient.begin(), [](unsigned char c){ return tolower(c); });
        input_ingredients.push_back(ingredient);
    }

   vector<string> possible_recipes = find_recipes(input_ingredients);

    if (possible_recipes.empty()) {
        cout << "Sorry, no recipes can be made with these ingredients.try your own expeiment \n";
    }
    else {
        
        cout << "\nYOU CAN PREPARE THE FOLLOWING POSSIBLE RECIPES:\n";
        for (const auto& recipe : possible_recipes) {
            cout << recipe << ": [";
            for(auto b : recipes[recipe]){
            cout <<" "<<b<<",";}
            cout << " ]"<<'\n';
        }
        
    }

    return 0;
}
